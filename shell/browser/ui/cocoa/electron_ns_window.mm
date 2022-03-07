#include "shell/browser/ui/cocoa/electron_ns_window.h"
#include "ui/base/cocoa/window_size_constants.h"

namespace electron {

}

@implementation ElectronNSWindow

- (id)initWithShell:(electron::NativeWindowMac*)shell
          styleMask:(NSUInteger)styleMask {
  if ((self = [super initWithContentRect:ui::kWindowSizeDeterminedLater
                               styleMask:styleMask
                                 backing:NSBackingStoreBuffered
                                   defer:NO])) {
    shell_ = shell;
  }
  return self;
}

- (electron::NativeWindowMac*)shell {
  return shell_;
}

@end