
#include "shell/browser/electron_browser_client.h"
#include "shell/browser/electron_browser_main_parts.h"


#include <memory>
#include <utility>

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
}