#include "base/mac/mac_util.h"
#include "components/remote_cocoa/app_shim/native_widget_ns_window_bridge.h"
#include "shell/browser/ui/cocoa/electron_ns_window_delegate.h"
#include "shell/browser/native_window_mac.h"
#include "ui/views/cocoa/native_widget_mac_ns_window_host.h"
#include "ui/views/widget/native_widget_mac.h"

#include <algorithm>

#include "shell/browser/ui/cocoa/electron_preview_item.h"

@implementation ElectronNSWindowDelegate
- (id)initWithShell:(electron::NativeWindowMac*)shell {
  auto* bridge_host = views::NativeWidgetMacNSWindowHost::GetFromNativeWindow(
      shell->GetNativeWindow());
  auto* bridged_view = bridge_host->GetInProcessNSWindowBridge();
  if ((self = [super initWithBridgedNativeWidget:bridged_view])) {
    shell_ = shell;
    is_zooming_ = false;
    level_ = [shell_->GetNativeWindow().GetNativeNSWindow() level];
  }
  return self;
}

#pragma mark - QLPreviewPanelDataSource

- (NSInteger)numberOfPreviewItemsInPreviewPanel:(QLPreviewPanel*)panel {
  return 1;
}

- (id<QLPreviewItem>)previewPanel:(QLPreviewPanel*)panel
               previewItemAtIndex:(NSInteger)index {
  return shell_->preview_item();
}

@end