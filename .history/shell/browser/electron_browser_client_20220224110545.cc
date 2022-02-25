#ifndef ELECTRON_SHELL_BROWSER_ELECTRON_BROWSER_CLIENT_H_
#define ELECTRON_SHELL_BROWSER_ELECTRON_BROWSER_CLIENT_H_

#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>


namespace content {}

namespace net {}

namespace electron {
  class ElectronBrowserMainParts;

  class ElectronBrowserClient : public content::ContentBrowserClient {
      ElectronBrowserClient();
      ~ElectronBrowserClient() override;

      // disable copy
      ElectronBrowserClient(const ElectronBrowserClient&) = delete;
      ElectronBrowserClient& operator=(const ElectronBrowserClient&) = delete;
  }
}


#endif  // ELECTRON_SHELL_BROWSER_ELECTRON_BROWSER_CLIENT_H_