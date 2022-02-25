// Copyright (c) 2013 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.



#include "shell/views/CrShellWindow.h"

namespace electron {
  void ElectronBrowserMainParts::PreCreateMainMessageLoop() {
    // Set our own application delegate.
    NSRect initial_window_bounds = NSMakeRect(0, 0, 100, 200);
    NSRect content_rect = initial_window_bounds;
    NSUInteger style_mask = NSTitledWindowMask | NSClosableWindowMask |
                            NSMiniaturizableWindowMask | NSResizableWindowMask;
                            
    CrShellWindow* window =
        [[CrShellWindow alloc] initWithContentRect:content_rect
                                         styleMask:style_mask
                                           backing:NSBackingStoreBuffered
                                             defer:NO];
    [window makeKeyAndOrderFront:nil];
    
    [NSApp run];   
  }
}