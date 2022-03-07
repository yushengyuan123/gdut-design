// Copyright (c) 2013 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "shell/browser/electron_browser_main_parts.h"

#include "base/mac/bundle_locations.h"
#import "shell/browser/mac/electron_application.h"
#include "shell/browser/mac/electron_application_delegate.h"

#include "shell/views/CrShellWindow.h"

namespace electron {
  void ElectronBrowserMainParts::PreCreateMainMessageLoop() {
    ElectronApplicationDelegate* delegate =
      [[ElectronApplicationDelegate alloc] init];
    [NSApp setDelegate:delegate];

    PreCreateMainMessageLoopCommon();

    // NSRect initial_window_bounds = NSMakeRect(0, 0, 100, 200);
    // NSRect content_rect = initial_window_bounds;
    // NSUInteger style_mask = NSTitledWindowMask | NSClosableWindowMask |
    //                         NSMiniaturizableWindowMask | NSResizableWindowMask;
                            
    // CrShellWindow* window =
    //     [[CrShellWindow alloc] initWithContentRect:content_rect
    //                                      styleMask:style_mask
    //                                        backing:NSBackingStoreBuffered
    //                                          defer:NO];
    // [window makeKeyAndOrderFront:nil];
  }

  void ElectronBrowserMainParts::RegisterURLHandler() {
    [[AtomApplication sharedApplication] registerURLHandler];
  }

  void ElectronBrowserMainParts::FreeAppDelegate() {
    [[NSApp delegate] release];
    [NSApp setDelegate:nil];
  }

  // Replicates NSApplicationMain, but doesn't start a run loop.
  void ElectronBrowserMainParts::InitializeMainNib() {
    auto infoDictionary = base::mac::OuterBundle().infoDictionary;

    auto principalClass =
        NSClassFromString([infoDictionary objectForKey:@"NSPrincipalClass"]);
    auto application = [principalClass sharedApplication];

    NSString* mainNibName = [infoDictionary objectForKey:@"NSMainNibFile"];

    NSNib* mainNib;

    @try {
      mainNib = [[NSNib alloc] initWithNibNamed:mainNibName
                                        bundle:base::mac::FrameworkBundle()];
      // Handle failure of initWithNibNamed on SMB shares
      // TODO(codebytere): Remove when
      // https://bugs.chromium.org/p/chromium/issues/detail?id=932935 is fixed
    } @catch (NSException* exception) {
      NSString* nibPath =
          [NSString stringWithFormat:@"Resources/%@.nib", mainNibName];
      nibPath = [base::mac::FrameworkBundle().bundlePath
          stringByAppendingPathComponent:nibPath];

      NSData* data = [NSData dataWithContentsOfFile:nibPath];
      mainNib = [[NSNib alloc] initWithNibData:data
                                        bundle:base::mac::FrameworkBundle()];
    }

    [mainNib instantiateWithOwner:application topLevelObjects:nil];
    [mainNib release];
  }
}