#include "shell/browser/api/electron_api_browser_window.h"

#include <memory>
#include <vector>

#import <Cocoa/Cocoa.h>

#include "base/mac/scoped_nsobject.h"
#include "shell/browser/native_window_mac.h"
#include "shell/browser/ui/electron_inspectable_web_contents_view.h"
#include "shell/browser/ui/inspectable_web_contents_view.h"

#include "shell/views/CrShellWindow.h"

namespace electron {
namespace api {
void BrowserWindow::OverrideNSWindowContentView(
    InspectableWebContentsView* view) {
  // Make NativeWindow use a NSView as content view.
  static_cast<NativeWindowMac*>(window())->OverrideNSWindowContentView();
  // Add webview to contentView.
  // view->GetNativeView 返回一个一个ElectronInspectableWebContentsView
  // 真的不知道这个GetNativeNSView是一个什么东西
  NSView* webView = view->GetNativeView().GetNativeNSView();
  // window()本质上是NativeWindowMac，
  // NativeWindowMac的GetNativeWindow()返回ElectronNSWindow* window_;
  NSView* contentView =
      [window()->GetNativeWindow().GetNativeNSWindow() contentView];

  [webView setFrame:[contentView bounds]];

  // ensure that buttons view is floated to top of view hierarchy
  NSArray* subviews = [contentView subviews];
  NSView* last = subviews.lastObject;
  [contentView addSubview:webView positioned:NSWindowBelow relativeTo:last];

  NSRect frame = [contentView bounds];

  [webView setFrame:frame];
  [webView setNeedsDisplay:YES];
}
}
}