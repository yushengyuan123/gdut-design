#include "shell/browser/javascript_environment.h"

#include <memory>
#include <string>
#include <unordered_set>
#include <utility>

#include "base/allocator/partition_alloc_features.h"
#include "base/allocator/partition_allocator/partition_alloc.h"
#include "base/command_line.h"
#include "base/feature_list.h"
#include "base/task/current_thread.h"
#include "base/task/thread_pool/initialization_util.h"
#include "base/threading/thread_task_runner_handle.h"
#include "base/trace_event/trace_event.h"
#include "gin/array_buffer.h"
#include "gin/v8_initializer.h"
#include "shell/common/node_includes.h"
#include "third_party/blink/public/common/switches.h"

namespace {
v8::Isolate* g_isolate;
}

namespace gin {}  // namespace gin

namespace electron {

class ArrayBufferAllocator : public v8::ArrayBuffer::Allocator {
 public:
  enum InitializationPolicy { kZeroInitialize, kDontInitialize };

  base::PartitionOptions::LazyCommit lazy_commit =
      base::FeatureList::IsEnabled(base::features::kPartitionAllocLazyCommit)
          ? base::PartitionOptions::LazyCommit::kEnabled
          : base::PartitionOptions::LazyCommit::kDisabled;

  ArrayBufferAllocator() {
    // Ref.
    // https://source.chromium.org/chromium/chromium/src/+/master:third_party/blink/renderer/platform/wtf/allocator/partitions.cc;l=94;drc=062c315a858a87f834e16a144c2c8e9591af2beb
    allocator_->init({base::PartitionOptions::AlignedAlloc::kDisallowed,
                      base::PartitionOptions::ThreadCache::kDisabled,
                      base::PartitionOptions::Quarantine::kAllowed,
                      base::PartitionOptions::Cookie::kAllowed,
                      base::PartitionOptions::BackupRefPtr::kDisabled,
                      base::PartitionOptions::UseConfigurablePool::kNo,
                      lazy_commit});
  }

  void* Allocate(size_t size) override {
    void* result = AllocateMemoryOrNull(size, kZeroInitialize);
    return result;
  }

  void* AllocateUninitialized(size_t size) override {
    void* result = AllocateMemoryOrNull(size, kDontInitialize);
    return result;
  }

  void Free(void* data, size_t size) override {
    allocator_->root()->Free(data);
  }

 private:
  static void* AllocateMemoryOrNull(size_t size, InitializationPolicy policy) {
    return AllocateMemoryWithFlags(size, policy,
                                   base::PartitionAllocReturnNull);
  }

  static void* AllocateMemoryWithFlags(size_t size,
                                       InitializationPolicy policy,
                                       int flags) {
    // The array buffer contents are sometimes expected to be 16-byte aligned in
    // order to get the best optimization of SSE, especially in case of audio
    // and video buffers.  Hence, align the given size up to 16-byte boundary.
    // Technically speaking, 16-byte aligned size doesn't mean 16-byte aligned
    // address, but this heuristics works with the current implementation of
    // PartitionAlloc (and PartitionAlloc doesn't support a better way for now).
    if (base::kAlignment <
        16) {  // base::kAlignment is a compile-time constant.
      size_t aligned_size = base::bits::AlignUp(size, 16);
      if (size == 0) {
        aligned_size = 16;
      }
      if (aligned_size >= size) {  // Only when no overflow
        size = aligned_size;
      }
    }

    if (policy == kZeroInitialize) {
      flags |= base::PartitionAllocZeroFill;
    }
    void* data = allocator_->root()->AllocFlags(flags, size, "Electron");
    if (base::kAlignment < 16) {
      char* ptr = reinterpret_cast<char*>(data);
      DCHECK_EQ(base::bits::AlignUp(ptr, 16), ptr)
          << "Pointer " << ptr << " not 16B aligned for size " << size;
    }
    return data;
  }

  static base::NoDestructor<base::PartitionAllocator> allocator_;
};

namespace {

int RunNodeInstance(node::MultiIsolatePlatform* platform,
                    const std::vector<std::string>& args,
                    const std::vector<std::string>& exec_args) {
  int exit_code = 0;

  // ?????? libuv ???????????????v8::Isolate????????? Node.js ??????
  std::vector<std::string> errors;
  std::unique_ptr<node::CommonEnvironmentSetup> setup =
      node::CommonEnvironmentSetup::Create(platform, &errors, args, exec_args);
  if (!setup) {
    for (const std::string& err : errors)
      fprintf(stderr, "%s: %s\n", args[0].c_str(), err.c_str());
    return 1;
  }

  v8::Isolate* isolate = setup->isolate();
  node::Environment* env = setup->env();

  {
    v8::Locker locker(isolate);
    v8::Isolate::Scope isolate_scope(isolate);
    // ????????? node::CreateEnvironment() ??? node::LoadEnvironment() ??????
    // ???????????? v8::Context???
    v8::Context::Scope context_scope(setup->context());

    // ?????????????????? Node.js ????????????????????????????????????
    // ??????????????????????????????
    // ??????????????? `require` ??? `process` ?????????
    // ?????????????????????????????????????????????????????????
    // ??????????????? `require` ??????????????????????????????
    // ?????????????????? Node.js ???????????????
    // `module.createRequire()` ??????????????????????????????????????????????????????
    // ?????????????????? CommonJS ???????????????
    // ?????????????????? `require` ?????????
    v8::MaybeLocal<v8::Value> loadenv_ret = node::LoadEnvironment(
        env,
        "const publicRequire ="
        "  require('module').createRequire(process.cwd() + '/');"
        "globalThis.require = publicRequire;"
        "require('vm').runInThisContext(process.argv[1]);");

    if (loadenv_ret.IsEmpty())  // ????????? JS ?????????
      return 1;

    exit_code = node::SpinEventLoop(env).FromMaybe(1);

    // node::Stop() ?????????????????????????????????????????????????????? JavaScript ?????????
    // ?????????????????????????????????
    // ??????????????????????????????????????? worker.terminate() ?????????
    node::Stop(env);
  }

  return exit_code;
}
}  // namespace

base::NoDestructor<base::PartitionAllocator> ArrayBufferAllocator::allocator_{};

// static
v8::Isolate* JavascriptEnvironment::GetIsolate() {
  CHECK(g_isolate);
  return g_isolate;
}

JavascriptEnvironment::JavascriptEnvironment(uv_loop_t* event_loop)
    : isolate_(Initialize(event_loop)),
      isolate_holder_(base::ThreadTaskRunnerHandle::Get(),
                      gin::IsolateHolder::kSingleThread,
                      gin::IsolateHolder::kAllowAtomicsWait,
                      gin::IsolateHolder::IsolateType::kUtility,
                      gin::IsolateHolder::IsolateCreationMode::kNormal,
                      nullptr,
                      nullptr,
                      isolate_),
      locker_(isolate_) {
  isolate_->Enter();
  v8::HandleScope scope(isolate_);
  auto context = node::NewContext(isolate_);
  context_ = v8::Global<v8::Context>(isolate_, context);
  context->Enter();
}

JavascriptEnvironment::~JavascriptEnvironment() {}

int JavascriptEnvironment::NodeStartup() {
  // int argc = 3;
  // char const** argv = new const char*;

  // argv[0] = "node";
  // argv[1] = "-e";
  // argv[2] = "console.log(1)";

  // ???????????????????????????????????????????????????
  v8::V8::InitializeExternalStartupData(
      "/Users/yushengyuan/yushengyuan/study/chromium1/src/out/testing/"
      "snapshot_blob.bin");

  // argv = uv_setup_args(argc, argv);
  std::vector<std::string> argv = {"electron"};
  std::vector<std::string> exec_argv;
  std::vector<std::string> errors;

  int exit_code = node::InitializeNodeWithArgs(&argv, &exec_argv, &errors);

  for (const std::string& error : errors)
    fprintf(stderr, "%s: %s\n", argv[0].c_str(), error.c_str());

  if (exit_code != 0) {
    return exit_code;
  }

  std::unique_ptr<node::MultiIsolatePlatform> platform =
      node::MultiIsolatePlatform::Create(4);
  v8::V8::InitializePlatform(platform.get());
  v8::V8::Initialize();

  int ret = RunNodeInstance(platform.get(), argv, exec_argv);

  return ret;
}

class TracingControllerImpl : public node::tracing::TracingController {
 public:
  TracingControllerImpl() = default;
  ~TracingControllerImpl() override = default;

  // disable copy
  TracingControllerImpl(const TracingControllerImpl&) = delete;
  TracingControllerImpl& operator=(const TracingControllerImpl&) = delete;
};

v8::Isolate* JavascriptEnvironment::Initialize(uv_loop_t* event_loop) {
  auto* cmd = base::CommandLine::ForCurrentProcess();
  // ???????????????????????????????????????????????????
  v8::V8::InitializeExternalStartupData(
      "/Users/yushengyuan/yushengyuan/study/chromium1/src/out/testing/"
      "snapshot_blob.bin");

  // --js-flags.
  std::string js_flags =
      cmd->GetSwitchValueASCII(blink::switches::kJavaScriptFlags);
  if (!js_flags.empty())
    v8::V8::SetFlagsFromString(js_flags.c_str(), js_flags.size());

  // The V8Platform of gin relies on Chromium's task schedule, which has not
  // been started at this point, so we have to rely on Node's V8Platform.
  // auto* tracing_agent = node::CreateAgent();
  auto* tracing_controller = new TracingControllerImpl();
  // node::tracing::TraceEventHelper::SetAgent(tracing_agent);
  platform_ = node::CreatePlatform(
      base::RecommendedMaxNumberOfThreadsInThreadGroup(3, 8, 0.1, 0),
      tracing_controller, gin::V8Platform::PageAllocator());
  v8::V8::InitializePlatform(platform_);
  gin::IsolateHolder::Initialize(gin::IsolateHolder::kNonStrictMode,
                                 new ArrayBufferAllocator(),
                                 nullptr /* external_reference_table */,
                                 js_flags, false /* create_v8_platform */);

  v8::Isolate* isolate = v8::Isolate::Allocate();
  platform_->RegisterIsolate(isolate, event_loop);
  g_isolate = isolate;

  return isolate;
}

NodeEnvironment::NodeEnvironment(node::Environment* env) : env_(env) {}

NodeEnvironment::~NodeEnvironment() {
  auto* isolate_data = env_->isolate_data();
  node::FreeEnvironment(env_);
  node::FreeIsolateData(isolate_data);
}

}  // namespace electron