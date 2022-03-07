#import "shell/browser/mac/electron_application_delegate.h"

#include <memory>
#include <string>

#include "base/allocator/allocator_shim.h"
#include "base/allocator/buildflags.h"
#include "base/mac/mac_util.h"
#include "base/mac/scoped_objc_class_swizzler.h"
#include "base/strings/sys_string_conversions.h"
#include "base/values.h"

@implementation ElectronApplicationDelegate

- (void)applicationDidFinishLaunching:(NSNotification*)notify {
  NSLog(@"applicationDidFinishLaunching");
}

// - (void)setApplicationDockMenu:(electron::ElectronMenuModel*)model {
//   menu_controller_.reset([[ElectronMenuController alloc] initWithModel:model
//                                                  useDefaultAccelerator:NO]);
// }

@end