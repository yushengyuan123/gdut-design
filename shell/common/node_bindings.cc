#include "shell/common/node_bindings.h"

#include <algorithm>
#include <memory>
#include <set>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>


#include "base/base_paths.h"
#include "base/command_line.h"
#include "base/environment.h"
#include "base/path_service.h"
#include "base/run_loop.h"
#include "base/strings/string_split.h"
#include "base/strings/utf_string_conversions.h"
#include "base/task/single_thread_task_runner.h"
#include "base/threading/thread_task_runner_handle.h"
#include "base/trace_event/trace_event.h"
#include "content/public/browser/browser_thread.h"
#include "content/public/common/content_paths.h"
#include "electron/buildflags/buildflags.h"
#include "electron/fuses.h"
#include "shell/common/electron_command_line.h"
#include "shell/common/gin_converters/file_path_converter.h"
#include "shell/common/gin_helper/dictionary.h"
#include "shell/common/mac/main_application_bundle.h"
// 有一个奇怪的问题加上这个头文件居然就可以使用node内部方法了
// 总之就很神奇
#include "shell/common/node_includes.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_initializer.h"

#define ELECTRON_BUILTIN_MODULES(V)      \
  V(electron_browser_app)                \
  V(electron_browser_view)               \
  V(electron_browser_window)             \
  V(electron_browser_event_emitter)      \
  V(electron_browser_web_contents_view)  \
  V(electron_common_asar)                \
  V(electron_common_v8_util)             \
  V(electron_browser_web_contents)       \
  
#define V(modname) void _register_##modname();
ELECTRON_BUILTIN_MODULES(V)

#undef V


namespace {
  bool g_is_initialized = false;

  const std::unordered_set<base::StringPiece, base::StringPieceHash>
  GetAllowedDebugOptions() {
    if (electron::fuses::IsNodeCliInspectEnabled()) {
      // Only allow DebugOptions in non-ELECTRON_RUN_AS_NODE mode
      return {
          "--inspect",          "--inspect-brk",
          "--inspect-port",     "--debug",
          "--debug-brk",        "--debug-port",
          "--inspect-brk-node", "--inspect-publish-uid",
      };
    }
    // If node CLI inspect support is disabled, allow no debug options.
    return {};
  }

  void SetNodeCliFlags() {
    const std::unordered_set<base::StringPiece, base::StringPieceHash> allowed =
        GetAllowedDebugOptions();

    const auto argv = base::CommandLine::ForCurrentProcess()->argv();
    std::vector<std::string> args;

    // TODO(codebytere): We need to set the first entry in args to the
    // process name owing to src/node_options-inl.h#L286-L290 but this is
    // redundant and so should be refactored upstream.
    args.reserve(argv.size() + 1);
    args.emplace_back("electron");

    for (const auto& arg : argv) {
  #if defined(OS_WIN)
      const auto& option = base::WideToUTF8(arg);
  #else
      const auto& option = arg;
  #endif
      const auto stripped = base::StringPiece(option).substr(0, option.find('='));

      // Only allow in no-op (--) option or DebugOptions
      if (allowed.count(stripped) != 0 || stripped == "--")
        args.push_back(option);
    }

    std::vector<std::string> errors;
    const int exit_code = ProcessGlobalArgs(&args, nullptr, &errors,
                                            node::kDisallowedInEnvironment);

    const std::string err_str = "Error parsing Node.js cli flags ";
    if (exit_code != 0) {
      std::cout << exit_code << std::endl;
    } else if (!errors.empty()) {
      std::cout << err_str << base::JoinString(errors, " ") << std::endl;
    }
    
  }

  void SetNodeOptions(base::Environment* env) {
    // // Options that are unilaterally disallowed
    // const std::set<std::string> disallowed = {
    //     "--openssl-config", "--use-bundled-ca", "--use-openssl-ca",
    //     "--force-fips", "--enable-fips"};

    // // Subset of options allowed in packaged apps
    // const std::set<std::string> allowed_in_packaged = {"--max-http-header-size",
    //                                                   "--http-parser"};

    // if (env->HasVar("NODE_OPTIONS")) {
    //   if (electron::fuses::IsNodeOptionsEnabled()) {
    //     std::string options;
    //     env->GetVar("NODE_OPTIONS", &options);
    //     std::vector<std::string> parts = base::SplitString(
    //         options, " ", base::TRIM_WHITESPACE, base::SPLIT_WANT_NONEMPTY);

    //     bool is_packaged_app = electron::api::App::IsPackaged();

    //     for (const auto& part : parts) {
    //       // Strip off values passed to individual NODE_OPTIONs
    //       std::string option = part.substr(0, part.find('='));

    //       if (is_packaged_app &&
    //           allowed_in_packaged.find(option) == allowed_in_packaged.end()) {
    //         // Explicitly disallow majority of NODE_OPTIONS in packaged apps
    //         LOG(ERROR) << "Most NODE_OPTIONs are not supported in packaged apps."
    //                   << " See documentation for more details.";
    //         options.erase(options.find(option), part.length());
    //       } else if (disallowed.find(option) != disallowed.end()) {
    //         // Remove NODE_OPTIONS specifically disallowed for use in Node.js
    //         // through Electron owing to constraints like BoringSSL.
    //         LOG(ERROR) << "The NODE_OPTION " << option
    //                   << " is not supported in Electron";
    //         options.erase(options.find(option), part.length());
    //       }
    //     }

    //     // overwrite new NODE_OPTIONS without unsupported variables
    //     env->SetVar("NODE_OPTIONS", options);
    //   } else {
    //     LOG(ERROR) << "NODE_OPTIONS have been disabled in this app";
    //     env->SetVar("NODE_OPTIONS", "");
    //   }
    // }

  }

}





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

  NodeBindings::~NodeBindings() {
  }

  void NodeBindings::LoadEnvironment(node::Environment* env) {
    node::LoadEnvironment(env, node::StartExecutionCallback{});
    // gin_helper::EmitEvent(env->isolate(), env->process_object(), "loaded");
  }

  node::Environment* NodeBindings::CreateEnvironment(
      v8::Handle<v8::Context> context,
      node::MultiIsolatePlatform* platform) {
    auto args = ElectronCommandLine::argv();    
    
    // Feed node the path to initialization script.
    std::string process_type;
    switch (browser_env_) {
      case BrowserEnvironment::kBrowser:
        process_type = "browser";
        break;
      case BrowserEnvironment::kRenderer:
        process_type = "renderer";
        break;
      case BrowserEnvironment::kWorker:
        process_type = "worker";
        break;
    }

    v8::Isolate* isolate = context->GetIsolate();

    if (browser_env_ == BrowserEnvironment::kBrowser) {
      const std::vector<std::string> search_paths = {"app.asar", "app",
                                                    "default_app.asar"};
      const std::vector<std::string> app_asar_search_paths = {"app.asar"};
      context->Global()->SetPrivate(
          context,
          v8::Private::ForApi(
              isolate,
              gin::ConvertToV8(isolate, "appSearchPaths").As<v8::String>()),
          gin::ConvertToV8(isolate,
                          electron::fuses::IsOnlyLoadAppFromAsarEnabled()
                              ? app_asar_search_paths
                              : search_paths));
    }

    std::vector<std::string> exec_args;
    base::FilePath resources_path = GetResourcesPath();

    std::string init_script = "electron/js2c/" + process_type + "_init";

    args.insert(args.begin() + 1, init_script);

    isolate_data_ =
        node::CreateIsolateData(isolate, uv_loop_, platform);

    node::Environment* env;
    uint64_t flags =  node::EnvironmentFlags::kDefaultFlags |
                      node::EnvironmentFlags::kHideConsoleWindows |
                      node::EnvironmentFlags::kNoGlobalSearchPaths;             

    printf("haha1\n");

    if (browser_env_ != BrowserEnvironment::kBrowser) {
      // Only one ESM loader can be registered per isolate -
      // in renderer processes this should be blink. We need to tell Node.js
      // not to register its handler (overriding blinks) in non-browser processes.
      flags |= node::EnvironmentFlags::kNoRegisterESMLoader |
              node::EnvironmentFlags::kNoInitializeInspector;
      v8::TryCatch try_catch(context->GetIsolate());
      env = node::CreateEnvironment(
          isolate_data_, context, args, exec_args,
          static_cast<node::EnvironmentFlags::Flags>(flags));
      DCHECK(env);

      // This will only be caught when something has gone terrible wrong as all
      // electron scripts are wrapped in a try {} catch {} by webpack
      if (try_catch.HasCaught()) {
        std::cout << "Failed to initialize node environment in process: " << process_type << std::endl;
      }
    } else {
      env = node::CreateEnvironment(
          isolate_data_, context, args, exec_args,
          static_cast<node::EnvironmentFlags::Flags>(flags));
      DCHECK(env);
    }
printf("haha2\n");
    gin_helper::Dictionary process(context->GetIsolate(), env->process_object());

    process.Set("resourcesPath", resources_path);
     
    return env;
  }

  void NodeBindings::RegisterBuiltinModules() {
  #define V(modname) _register_##modname();
    ELECTRON_BUILTIN_MODULES(V)
  #undef V  
  }

  void NodeBindings::Initialize() {
    // Explicitly register electron's builtin modules.
    RegisterBuiltinModules();

    // Parse and set Node.js cli flags.
    SetNodeCliFlags();

    auto env = base::Environment::Create();
    SetNodeOptions(env.get());

    std::vector<std::string> argv = {"electron"};
    std::vector<std::string> exec_argv;
    std::vector<std::string> errors;
    // 初始化node的核心模块
    int exit_code = node::InitializeNodeWithArgs(&argv, &exec_argv, &errors);

    for (const std::string& error : errors)
      fprintf(stderr, "%s: %s\n", argv[0].c_str(), error.c_str());

    if (exit_code != 0)
      exit(exit_code);

    g_is_initialized = true;  
  }
}