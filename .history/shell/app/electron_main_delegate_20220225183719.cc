#include "shell/app/electron_main_delegate.h"

#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "base/base_switches.h"
#include "base/command_line.h"
#include "base/environment.h"
#include "base/files/file_util.h"
#include "base/logging.h"
#include "base/mac/bundle_locations.h"
#include "base/path_service.h"
#include "base/strings/string_split.h"
#include "chrome/common/chrome_paths.h"
#include "chrome/common/chrome_switches.h"
#include "components/content_settings/core/common/content_settings_pattern.h"
#include "content/public/common/content_switches.h"
#include "electron/buildflags/buildflags.h"
#include "extensions/common/constants.h"
#include "ipc/ipc_buildflags.h"
#include "sandbox/policy/switches.h"
#include "services/tracing/public/cpp/stack_sampling/tracing_sampler_profiler.h"

#include "shell/app/electron_content_client.h"
#include "shell/browser/electron_browser_client.h"
#include "shell/browser/electron_gpu_client.h"
#include "shell/common/application_info.h"
#include "shell/common/electron_paths.h"
#include "shell/renderer/electron_renderer_client.h"
#include "shell/utility/electron_content_utility_client.h"

#include "ui/base/resource/resource_bundle.h"
#include "ui/base/ui_base_switches.h"

#if defined(OS_MAC)
#include "shell/app/electron_main_delegate_mac.h"
#endif

namespace electron {

namespace {
const char kRelauncherProcess[] = "relauncher";
constexpr base::StringPiece kElectronDisableSandbox("ELECTRON_DISABLE_SANDBOX");
// constexpr base::StringPiece
// kElectronEnableStackDumping("ELECTRON_ENABLE_STACK_DUMPING");

// bool IsBrowserProcess(base::CommandLine* cmd) {
// 	std::string process_type =
// cmd->GetSwitchValueASCII(::switches::kProcessType); 	return
// process_type.empty();
// }

bool ElectronPathProvider(int key, base::FilePath* result) {
  bool create_dir = false;
  base::FilePath cur;
  switch (key) {
    case chrome::DIR_USER_DATA:
      if (!base::PathService::Get(DIR_APP_DATA, &cur))
        return false;
      cur = cur.Append(base::FilePath::FromUTF8Unsafe(
          GetPossiblyOverriddenApplicationName()));
      create_dir = true;
      break;
    case DIR_CRASH_DUMPS:
      if (!base::PathService::Get(chrome::DIR_USER_DATA, &cur))
        return false;
      cur = cur.Append(FILE_PATH_LITERAL("Crashpad"));
      create_dir = true;
      break;
    case chrome::DIR_APP_DICTIONARIES:
      // TODO(nornagon): can we just default to using Chrome's logic here?
      if (!base::PathService::Get(chrome::DIR_USER_DATA, &cur))
        return false;
      cur = cur.Append(base::FilePath::FromUTF8Unsafe("Dictionaries"));
      create_dir = true;
      break;
    case DIR_USER_CACHE: {
#if defined(OS_POSIX)
      int parent_key = base::DIR_CACHE;
#else
      // On Windows, there's no OS-level centralized location for caches, so
      // store the cache in the app data directory.
      int parent_key = base::DIR_ROAMING_APP_DATA;
#endif
      if (!base::PathService::Get(parent_key, &cur))
        return false;
      cur = cur.Append(base::FilePath::FromUTF8Unsafe(
          GetPossiblyOverriddenApplicationName()));
      create_dir = true;
      break;
    }
#if defined(OS_LINUX)
    case DIR_APP_DATA: {
      auto env = base::Environment::Create();
      cur = base::nix::GetXDGDirectory(
          env.get(), base::nix::kXdgConfigHomeEnvVar, base::nix::kDotConfigDir);
      break;
    }
#endif
#if defined(OS_WIN)
    case DIR_RECENT:
      if (!platform_util::GetFolderPath(DIR_RECENT, &cur))
        return false;
      create_dir = true;
      break;
#endif
    case DIR_APP_LOGS:
#if defined(OS_MAC)
      if (!base::PathService::Get(base::DIR_HOME, &cur))
        return false;
      cur = cur.Append(FILE_PATH_LITERAL("Library"));
      cur = cur.Append(FILE_PATH_LITERAL("Logs"));
      cur = cur.Append(base::FilePath::FromUTF8Unsafe(
          GetPossiblyOverriddenApplicationName()));
#else
      if (!base::PathService::Get(chrome::DIR_USER_DATA, &cur))
        return false;
      cur = cur.Append(base::FilePath::FromUTF8Unsafe("logs"));
#endif
      create_dir = true;
      break;
    default:
      return false;
  }

  // TODO(bauerb): http://crbug.com/259796
  // base::ThreadRestrictions::ScopedAllowIO allow_io;
  if (create_dir && !base::PathExists(cur) && !base::CreateDirectory(cur)) {
    return false;
  }

  *result = cur;

  return true;
}

void RegisterPathProvider() {
  base::PathService::RegisterProvider(ElectronPathProvider, PATH_START,
                                      PATH_END);
}
}  // namespace
// 这个应该是找resources.pak路径
std::string LoadResourceBundle(const std::string& locale) {
  const bool initialized = ui::ResourceBundle::HasSharedInstance();
  DCHECK(!initialized);

  // Load other resource files.
  base::FilePath pak_dir;
#if defined(OS_MAC)
  pak_dir =
      base::mac::FrameworkBundlePath().Append(FILE_PATH_LITERAL("Resources"));
#else
  base::PathService::Get(base::DIR_MODULE, &pak_dir);
#endif

  std::string loaded_locale = ui::ResourceBundle::InitSharedInstanceWithLocale(
      locale, nullptr, ui::ResourceBundle::LOAD_COMMON_RESOURCES);
  ui::ResourceBundle& bundle = ui::ResourceBundle::GetSharedInstance();
  bundle.AddDataPackFromPath(pak_dir.Append(FILE_PATH_LITERAL("resources.pak")),
                             ui::kScaleFactorNone);
  return loaded_locale;
}

ElectronMainDelegate::ElectronMainDelegate() = default;

ElectronMainDelegate::~ElectronMainDelegate() = default;

const char* const ElectronMainDelegate::kNonWildcardDomainNonPortSchemes[] = {
    extensions::kExtensionScheme};
const size_t ElectronMainDelegate::kNonWildcardDomainNonPortSchemesSize =
    base::size(kNonWildcardDomainNonPortSchemes);

bool ElectronMainDelegate::BasicStartupComplete(int* exit_code) {
  auto* command_line = base::CommandLine::ForCurrentProcess();

  auto env = base::Environment::Create();

  // if (env->HasVar(kElectronEnableStackDumping))
  // 	base::debug::EnableInProcessStackDumping();

  if (env->HasVar(kElectronDisableSandbox))
    command_line->AppendSwitch(sandbox::policy::switches::kNoSandbox);

  tracing_sampler_profiler_ =
      tracing::TracingSamplerProfiler::CreateOnMainThread();
  // 这个RegisterPathProvider，是用来注册一个provider去查找某些配置文件的
  // http://blog.chinaunix.net/uid-10638908-id-2944564.html
  chrome::RegisterPathProvider();
  electron::RegisterPathProvider();

  // #if BUILDFLAG(ENABLE_ELECTRON_EXTENSIONS)
  // ContentSettingsPattern::SetNonWildcardDomainNonPortSchemes(
  // 				kNonWildcardDomainNonPortSchemes,
  // kNonWildcardDomainNonPortSchemesSize); #endif

  OverrideChildProcessPath();
  OverrideFrameworkBundlePath();
  SetUpBundleOverrides();

  // 这句代码的的作用很关键，content_client_这个东西影响后续的桌面程序的展示
  content_client_ = std::make_unique<ElectronContentClient>();
  SetContentClient(content_client_.get());

  return false;
}

absl::variant<int, content::MainFunctionParams> 
ElectronMainDelegate::RunProcess(
	const std::string& process_type,
	content::MainFunctionParams main_function_params) {
		if (process_type == kRelauncherProcess) {
			printf("kRelauncherProcess\n");
		}

    return std::move(main_function_params);
}


bool ElectronMainDelegate::ShouldCreateFeatureList() {
  return false;
}

bool ElectronMainDelegate::ShouldLockSchemeRegistry() {
  return false;
}

content::ContentBrowserClient*
ElectronMainDelegate::CreateContentBrowserClient() {
  browser_client_ = std::make_unique<ElectronBrowserClient>();
  return browser_client_.get();
}

content::ContentGpuClient* ElectronMainDelegate::CreateContentGpuClient() {
  gpu_client_ = std::make_unique<ElectronGpuClient>();
  return gpu_client_.get();
}

content::ContentRendererClient*
ElectronMainDelegate::CreateContentRendererClient() {
  // auto* command_line = base::CommandLine::ForCurrentProcess();

  // if (IsSandboxEnabled(command_line)) {
  //   renderer_client_ = std::make_unique<ElectronSandboxedRendererClient>();
  // } else {
  //   renderer_client_ = std::make_unique<ElectronRendererClient>();
  // }
  renderer_client_ = std::make_unique<ElectronRendererClient>();

  return renderer_client_.get();
}

content::ContentUtilityClient*
ElectronMainDelegate::CreateContentUtilityClient() {
  utility_client_ = std::make_unique<ElectronContentUtilityClient>();
  return utility_client_.get();
}
};  // namespace electron