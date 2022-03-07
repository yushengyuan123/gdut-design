#include "base/base_switches.h"
#include "base/command_line.h"
#include "base/files/file_util.h"
#include "base/path_service.h"
#include "chrome/browser/browser_process.h"
#include "chrome/common/chrome_paths.h"
#include "chrome/common/chrome_switches.h"
#include "chrome/common/chrome_version.h"
#include "content/public/common/content_switches.h"
#include "shell/browser/electron_browser_client.h"
#include "shell/browser/electron_browser_main_parts.h"
#include "shell/common/options_switches.h"


#include <memory>
#include <utility>

#if defined(OS_MAC)
#include "content/common/mac_helpers.h"
#include "content/public/common/child_process_host.h"
#endif

namespace electron {
  namespace {
    ElectronBrowserClient* g_browser_client = nullptr;
  }

  // static
  ElectronBrowserClient* ElectronBrowserClient::Get() {
    return g_browser_client;
  }

  ElectronBrowserClient::ElectronBrowserClient() {
    // DCHECK(!g_browser_client);
    g_browser_client = this;
  }

  ElectronBrowserClient::~ElectronBrowserClient() {
    // DCHECK(g_browser_client);
    g_browser_client = nullptr;
  }

  std::unique_ptr<content::BrowserMainParts>
  ElectronBrowserClient::CreateBrowserMainParts(
      content::MainFunctionParams params) {
    auto browser_main_parts =
        std::make_unique<ElectronBrowserMainParts>(std::move(params));

  #if defined(OS_MAC)
    browser_main_parts_ = browser_main_parts.get();
  #endif

    return browser_main_parts;
  }

  void ElectronBrowserClient::AppendExtraCommandLineSwitches(
      base::CommandLine* command_line,
      int process_id) {

    // Make sure we're about to launch a known executable
    {
      base::ThreadRestrictions::ScopedAllowIO allow_io;
      base::FilePath child_path;
      base::FilePath program =
          base::MakeAbsoluteFilePath(command_line->GetProgram());
  #if defined(OS_MAC)
      auto renderer_child_path = content::ChildProcessHost::GetChildPath(
          content::ChildProcessHost::CHILD_RENDERER);
      auto gpu_child_path = content::ChildProcessHost::GetChildPath(
          content::ChildProcessHost::CHILD_GPU);
  #if BUILDFLAG(ENABLE_PLUGINS)
      auto plugin_child_path = content::ChildProcessHost::GetChildPath(
          content::ChildProcessHost::CHILD_PLUGIN);
  #endif
      if (program != renderer_child_path && program != gpu_child_path
  #if BUILDFLAG(ENABLE_PLUGINS)
          && program != plugin_child_path
  #endif
      ) {
        child_path = content::ChildProcessHost::GetChildPath(
            content::ChildProcessHost::CHILD_NORMAL);
        CHECK_EQ(program, child_path)
            << "Aborted from launching unexpected helper executable";
      }
  #endif
    }

    std::string process_type =
        command_line->GetSwitchValueASCII(::switches::kProcessType);

    // // The zygote process is booted before JS runs, so DIR_USER_DATA isn't usable
    // // at that time. It doesn't need --user-data-dir to be correct anyway, since
    // // the zygote itself doesn't access anything in that directory.
    if (process_type != ::switches::kZygoteProcess) {
      base::FilePath user_data_dir;
      if (base::PathService::Get(chrome::DIR_USER_DATA, &user_data_dir))
        command_line->AppendSwitchPath(::switches::kUserDataDir, user_data_dir);
    }

  }
}