#include "shell/browser/shell_platform_delegate.h"
#include "shell/browser/shell.h"

#include "shell/views/CrShellWindow.h"

namespace electron {
  void ShellPlatformDelegate::CreatePlatformWindow(Shell* shell) {
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
  
  }
}