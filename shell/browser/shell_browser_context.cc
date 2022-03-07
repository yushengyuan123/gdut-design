#include "shell/browser/shell_browser_context.h"
#include "content/public/browser/resource_context.h"

#include <memory>
#include <utility>

namespace electron { 

  ShellBrowserContext::ShellResourceContext::ShellResourceContext() {}

  ShellBrowserContext::ShellResourceContext::~ShellResourceContext() {
  }

  ShellBrowserContext::ShellBrowserContext(bool off_the_record,
                                          bool delay_services_creation)
      : resource_context_(std::make_unique<ShellResourceContext>()),
        off_the_record_(off_the_record) {

          if (off_the_record_) {
            printf("111\n");
          }
  }

  ShellBrowserContext::~ShellBrowserContext() {
  }

  void ShellBrowserContext::InitWhileIOAllowed() {
    base::CommandLine* cmd_line = base::CommandLine::ForCurrentProcess();
    if (cmd_line->HasSwitch(switches::kIgnoreCertificateErrors))
      ignore_certificate_errors_ = true;
    if (cmd_line->HasSwitch(switches::kContentShellDataPath)) {
      path_ = cmd_line->GetSwitchValuePath(switches::kContentShellDataPath);
      if (base::DirectoryExists(path_) || base::CreateDirectory(path_))  {
        // BrowserContext needs an absolute path, which we would normally get via
        // PathService. In this case, manually ensure the path is absolute.
        if (!path_.IsAbsolute())
          path_ = base::MakeAbsoluteFilePath(path_);
        if (!path_.empty()) {
          FinishInitWhileIOAllowed();
          return;
        }
      } else {
        LOG(WARNING) << "Unable to create data-path directory: " << path_.value();
      }
    }

    CHECK(base::PathService::Get(SHELL_DIR_USER_DATA, &path_));

    FinishInitWhileIOAllowed();
  }
}