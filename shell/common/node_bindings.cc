#include "shell/common/node_bindings.h"

#include <algorithm>
#include <memory>
#include <set>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>
// 有一个奇怪的问题加上这个头文件居然就可以使用node内部方法了
// 总之就很神奇
#include "shell/common/node_includes.h"

namespace electron {
  namespace {
    base::FilePath GetResourcesPath() {
      return MainApplicationBundlePath().Append("Contents").Append("Resources");
    }
  }

  NodeBindings::NodeBindings(BrowserEnvironment browser_env)
      : browser_env_(browser_env) {
    // 初始化libuv    
    if (browser_env == BrowserEnvironment::kWorker) {
      // uv_loop_init(&worker_loop_);
      // uv_loop_ = &worker_loop_;
      printf("init kworker\n");
    } else {
      uv_loop_ = uv_default_loop();
    }
  }

  void NodeBindings::LoadEnvironment() {
    node::LoadEnvironment();
    // gin_helper::EmitEvent(env->isolate(), env->process_object(), "loaded");
  }

  // node::Environment* NodeBindings::CreateEnvironment(
  //     v8::Handle<v8::Context> context,
  //     node::MultiIsolatePlatform* platform) {

  //   auto args = ElectronCommandLine::argv();

  //   // Feed node the path to initialization script.
  //   std::string process_type;
  //   switch (browser_env_) {
  //     case BrowserEnvironment::kBrowser:
  //       process_type = "browser";
  //       break;
  //     case BrowserEnvironment::kRenderer:
  //       process_type = "renderer";
  //       break;
  //     case BrowserEnvironment::kWorker:
  //       process_type = "worker";
  //       break;
  //   }

  //   v8::Isolate* isolate = context->GetIsolate();
  //   gin_helper::Dictionary global(isolate, context->Global());
  //   // Do not set DOM globals for renderer process.
  //   // We must set this before the node bootstrapper which is run inside
  //   // CreateEnvironment
  //   if (browser_env_ != BrowserEnvironment::kBrowser)
  //     global.Set("_noBrowserGlobals", true);

  //   if (browser_env_ == BrowserEnvironment::kBrowser) {
  //     const std::vector<std::string> search_paths = {"app.asar", "app",
  //                                                   "default_app.asar"};
  //     const std::vector<std::string> app_asar_search_paths = {"app.asar"};
  //     context->Global()->SetPrivate(
  //         context,
  //         v8::Private::ForApi(
  //             isolate,
  //             gin::ConvertToV8(isolate, "appSearchPaths").As<v8::String>()),
  //         gin::ConvertToV8(isolate,
  //                         electron::fuses::IsOnlyLoadAppFromAsarEnabled()
  //                             ? app_asar_search_paths
  //                             : search_paths));
  //   }

  //   std::vector<std::string> exec_args;
  //   base::FilePath resources_path = GetResourcesPath();
  //   std::string init_script = "electron/js2c/" + process_type + "_init";

  //   args.insert(args.begin() + 1, init_script);

  //   isolate_data_ =
  //       node::CreateIsolateData(context->GetIsolate(), uv_loop_, platform);

  //   node::Environment* env;
  //   uint64_t flags = node::EnvironmentFlags::kDefaultFlags |
  //                   node::EnvironmentFlags::kHideConsoleWindows |
  //                   node::EnvironmentFlags::kNoGlobalSearchPaths;

  //   if (browser_env_ != BrowserEnvironment::kBrowser) {
  //     // Only one ESM loader can be registered per isolate -
  //     // in renderer processes this should be blink. We need to tell Node.js
  //     // not to register its handler (overriding blinks) in non-browser processes.
  //     flags |= node::EnvironmentFlags::kNoRegisterESMLoader |
  //             node::EnvironmentFlags::kNoInitializeInspector;
  //     v8::TryCatch try_catch(context->GetIsolate());
  //     env = node::CreateEnvironment(
  //         isolate_data_, context, args, exec_args,
  //         static_cast<node::EnvironmentFlags::Flags>(flags));
  //     DCHECK(env);

  //     // This will only be caught when something has gone terrible wrong as all
  //     // electron scripts are wrapped in a try {} catch {} by webpack
  //     if (try_catch.HasCaught()) {
  //       LOG(ERROR) << "Failed to initialize node environment in process: "
  //                 << process_type;
  //     }
  //   } else {
  //     env = node::CreateEnvironment(
  //         isolate_data_, context, args, exec_args,
  //         static_cast<node::EnvironmentFlags::Flags>(flags));
  //     DCHECK(env);
  //   }

  //   // Clean up the global _noBrowserGlobals that we unironically injected into
  //   // the global scope
  //   if (browser_env_ != BrowserEnvironment::kBrowser) {
  //     // We need to bootstrap the env in non-browser processes so that
  //     // _noBrowserGlobals is read correctly before we remove it
  //     global.Delete("_noBrowserGlobals");
  //   }

  //   node::IsolateSettings is;

  //   // Use a custom fatal error callback to allow us to add
  //   // crash message and location to CrashReports.
  //   is.fatal_error_callback = V8FatalErrorCallback;

  //   // We don't want to abort either in the renderer or browser processes.
  //   // We already listen for uncaught exceptions and handle them there.
  //   is.should_abort_on_uncaught_exception_callback = [](v8::Isolate*) {
  //     return false;
  //   };

  //   // Use a custom callback here to allow us to leverage Blink's logic in the
  //   // renderer process.
  //   is.allow_wasm_code_generation_callback = AllowWasmCodeGenerationCallback;

  //   if (browser_env_ == BrowserEnvironment::kBrowser) {
  //     // Node.js requires that microtask checkpoints be explicitly invoked.
  //     is.policy = v8::MicrotasksPolicy::kExplicit;
  //   } else {
  //     // Blink expects the microtasks policy to be kScoped, but Node.js expects it
  //     // to be kExplicit. In the renderer, there can be many contexts within the
  //     // same isolate, so we don't want to change the existing policy here, which
  //     // could be either kExplicit or kScoped depending on whether we're executing
  //     // from within a Node.js or a Blink entrypoint. Instead, the policy is
  //     // toggled to kExplicit when entering Node.js through UvRunOnce.
  //     is.policy = context->GetIsolate()->GetMicrotasksPolicy();

  //     // We do not want to use Node.js' message listener as it interferes with
  //     // Blink's.
  //     is.flags &= ~node::IsolateSettingsFlags::MESSAGE_LISTENER_WITH_ERROR_LEVEL;

  //     // Isolate message listeners are additive (you can add multiple), so instead
  //     // we add an extra one here to ensure that the async hook stack is properly
  //     // cleared when errors are thrown.
  //     context->GetIsolate()->AddMessageListenerWithErrorLevel(
  //         ErrorMessageListener, v8::Isolate::kMessageError);

  //     // We do not want to use the promise rejection callback that Node.js uses,
  //     // because it does not send PromiseRejectionEvents to the global script
  //     // context. We need to use the one Blink already provides.
  //     is.flags |=
  //         node::IsolateSettingsFlags::SHOULD_NOT_SET_PROMISE_REJECTION_CALLBACK;

  //     // We do not want to use the stack trace callback that Node.js uses,
  //     // because it relies on Node.js being aware of the current Context and
  //     // that's not always the case. We need to use the one Blink already
  //     // provides.
  //     is.flags |=
  //         node::IsolateSettingsFlags::SHOULD_NOT_SET_PREPARE_STACK_TRACE_CALLBACK;
  //   }

  //   node::SetIsolateUpForNode(context->GetIsolate(), is);

  //   gin_helper::Dictionary process(context->GetIsolate(), env->process_object());
  //   process.SetReadOnly("type", process_type);
  //   process.Set("resourcesPath", resources_path);
  //   // The path to helper app.
  //   base::FilePath helper_exec_path;
  //   base::PathService::Get(content::CHILD_PROCESS_EXE, &helper_exec_path);
  //   process.Set("helperExecPath", helper_exec_path);

  //   return env;
  // }

  void NodeBindings::Initialize() {
    std::vector<std::string> argv = {"electron"};
    std::vector<std::string> exec_argv;
    std::vector<std::string> errors;
    // 初始化node的核心模块
    int exit_code = node::InitializeNodeWithArgs(&argv, &exec_argv, &errors);
    printf("caonima:%d\n", exit_code);
  }
}