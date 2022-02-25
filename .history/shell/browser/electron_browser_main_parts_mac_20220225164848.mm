// Copyright (c) 2013 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include 

namespace electron {
  void ElectronBrowserMainParts::PreCreateMainMessageLoop() {
    // Set our own application delegate.
    ElectronApplicationDelegate* delegate =
        [[ElectronApplicationDelegate alloc] init];
  }
}