//
// Created by 余圣源 on 2022/2/11.
//
#include "content/public/app/content_main.h"
#include "shell/app/electron_library_main.h"
#include "shell/app/electron_main_delegate.h"
#include "shell/app/electron_main_delegate_mac.h"
#include "shell/common/electron_command_line.h"

#include "shell/browser/electron_browser_main_parts.h"

#include "shell/views/CrShellWindow.h"

using namespace electron;

int ElectronMain(int argc, char* argv[]) {
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

		return 1;   
}