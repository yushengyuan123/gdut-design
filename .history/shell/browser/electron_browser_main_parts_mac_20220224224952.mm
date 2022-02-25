// Copyright (c) 2013 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "shell/browser/electron_browser_main_parts.h"
#include "shell/browser/mac/electron_application_delegate.h"

namespace electron {
  void ElectronBrowserMainParts::PreCreateMainMessageLoop() {
    // Set our own application delegate.
    ElectronApplicationDelegate* delegate =
        [[ElectronApplicationDelegate alloc] init];
    [NSApp setDelegate:delegate];

    PreCreateMainMessageLoopCommon();

    // Prevent Cocoa from turning command-line arguments into
    // |-application:openFiles:|, since we already handle them directly.
    [[NSUserDefaults standardUserDefaults]
        setObject:@"NO"
          forKey:@"NSTreatUnknownArgumentsAsOpen"];

    geolocation_manager_ = device::GeolocationManagerImpl::Create();
  }
}