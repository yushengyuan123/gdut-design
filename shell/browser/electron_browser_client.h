#ifndef ELECTRON_SHELL_BROWSER_ELECTRON_BROWSER_CLIENT_H_
#define ELECTRON_SHELL_BROWSER_ELECTRON_BROWSER_CLIENT_H_

#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include "base/files/file_path.h"
#include "base/synchronization/lock.h"
#include "content/public/browser/content_browser_client.h"
#include "content/public/browser/render_process_host_observer.h"
#include "content/public/browser/web_contents.h"



namespace content {}

namespace net {}

namespace electron {
  class ElectronBrowserMainParts;

  class ElectronBrowserClient : public content::ContentBrowserClient {
      public:
        static ElectronBrowserClient* Get();

        ElectronBrowserClient();
        ~ElectronBrowserClient() override;

        // disable copy
        ElectronBrowserClient(const ElectronBrowserClient&) = delete;
        ElectronBrowserClient& operator=(const ElectronBrowserClient&) = delete;

      protected:
        std::unique_ptr<content::BrowserMainParts> CreateBrowserMainParts(content::MainFunctionParams params) override;        

        void AppendExtraCommandLineSwitches(base::CommandLine* command_line,
                                      int child_process_id) override;

      private:

        #if defined(OS_MAC)
          ElectronBrowserMainParts* browser_main_parts_ = nullptr;
        #endif

  };
}


#endif  // ELECTRON_SHELL_BROWSER_ELECTRON_BROWSER_CLIENT_H_