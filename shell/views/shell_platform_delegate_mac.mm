
#include "shell/views/shell_platform_delegate.h"

#include "base/containers/contains.h"
#include "shell/views/shell.h"

#include "shell/views/CrShellWindow.h"

#include "url/gurl.h"

namespace electron {
  struct ShellPlatformDelegate::ShellData {
    gfx::NativeWindow window;
    NSTextField* url_edit_view = nullptr;
  };

  ShellPlatformDelegate::ShellPlatformDelegate() = default;
  ShellPlatformDelegate::~ShellPlatformDelegate() = default;
  
  void ShellPlatformDelegate::CreatePlatformWindow(Shell* shell) {
    DCHECK(!base::Contains(shell_data_map_, shell));
    ShellData& shell_data = shell_data_map_[shell];

    // Set our own application delegate.
    NSRect initial_window_bounds = NSMakeRect(0, 0, 800, 600);
    NSRect content_rect = initial_window_bounds;
    NSUInteger style_mask = NSTitledWindowMask | NSClosableWindowMask |
                            NSMiniaturizableWindowMask | NSResizableWindowMask;
                            
    CrShellWindow* window =
        [[CrShellWindow alloc] initWithContentRect:content_rect
                                         styleMask:style_mask
                                           backing:NSBackingStoreBuffered
                                             defer:NO];
    [window makeKeyAndOrderFront:nil];

    shell_data.window = window;
  }

  void ShellPlatformDelegate::SetContents(Shell* shell) {
    DCHECK(base::Contains(shell_data_map_, shell));
    ShellData& shell_data = shell_data_map_[shell];

    NSView* web_view = shell->web_contents()->GetNativeView().GetNativeNSView();
    [web_view setAutoresizingMask:(NSViewWidthSizable | NSViewHeightSizable)];

    NSView* content = [shell_data.window.GetNativeNSWindow() contentView];
    [content addSubview:web_view];

    NSRect frame = [content bounds];

    [web_view setFrame:frame];
    [web_view setNeedsDisplay:YES];
  }
}