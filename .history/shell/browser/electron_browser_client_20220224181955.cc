
#include "shell/browser/electron_browser_client.h"
#include "shell/browser/electron_browser_main_parts.h"


#include <memory>
#include <utility>

namespace electron {
  namespace {}

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
}