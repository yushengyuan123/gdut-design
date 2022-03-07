#include "shell/browser/api/electron_api_browser_window.h"

#include <memory>
#include <vector>

#import <Cocoa/Cocoa.h>

#include "base/mac/scoped_nsobject.h"
#include "shell/browser/native_window_mac.h"
#include "shell/browser/ui/electron_inspectable_web_contents_view.h"
#include "shell/browser/ui/inspectable_web_contents_view.h"

namespace electron {
  namespace api {
    void BrowserWindow::OverrideNSWindowContentView(
          InspectableWebContentsView* view) {
        // Add webview to contentView.
        // NSView* webView = view->GetNativeView().GetNativeNSView();
    }
  }
}