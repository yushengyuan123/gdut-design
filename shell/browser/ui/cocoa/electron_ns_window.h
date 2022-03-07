// Copyright (c) 2018 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef ELECTRON_SHELL_BROWSER_UI_COCOA_ELECTRON_NS_WINDOW_H_
#define ELECTRON_SHELL_BROWSER_UI_COCOA_ELECTRON_NS_WINDOW_H_

#include "components/remote_cocoa/app_shim/native_widget_mac_nswindow.h"
#include "ui/views/widget/native_widget_mac.h"

namespace electron {

class NativeWindowMac;
}

@interface ElectronNSWindow : NativeWidgetMacNSWindow {
 @private
  electron::NativeWindowMac* shell_;
}

- (id)initWithShell:(electron::NativeWindowMac*)shell
          styleMask:(NSUInteger)styleMask;
- (electron::NativeWindowMac*)shell;

@end
// Prevents window from resizing during the scope.

#endif  // ELECTRON_SHELL_BROWSER_UI_COCOA_ELECTRON_NS_WINDOW_H_
