#ifndef ELECTRON_SHELL_BROWSER_API_ELECTRON_API_BROWSER_WINDOW_H_
#define ELECTRON_SHELL_BROWSER_API_ELECTRON_API_BROWSER_WINDOW_H_

#include <string>
#include <vector>

#include "shell/browser/api/electron_api_base_window.h"

namespace electron {
  namespace api {
    class BrowserWindow : public BaseWindow {
      public:
          // disable copy
          BrowserWindow(const BrowserWindow&) = delete;
          BrowserWindow& operator=(const BrowserWindow&) = delete;

      protected:
        BrowserWindow(gin::Arguments* args, const gin_helper::Dictionary& options);
        ~BrowserWindow() override;

      private:
        void OverrideNSWindowContentView(InspectableWebContentsView* webView);      
    };
  }
}


#endif