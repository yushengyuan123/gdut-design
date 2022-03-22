#import "shell/browser/mac/electron_application_delegate.h"

#include <memory>
#include <string>

#include "base/allocator/allocator_shim.h"
#include "base/allocator/buildflags.h"
#include "base/mac/mac_util.h"
#include "base/mac/scoped_objc_class_swizzler.h"
#include "base/strings/sys_string_conversions.h"
#include "base/values.h"

#include "shell/browser/browser.h"
#include "shell/browser/mac/dict_util.h"
#import "shell/browser/mac/electron_application.h"

#import <UserNotifications/UserNotifications.h>

static NSDictionary* UNNotificationResponseToNSDictionary(
    UNNotificationResponse* response) API_AVAILABLE(macosx(10.14)) {
  // [response isKindOfClass:[UNNotificationResponse class]]
  if (![response respondsToSelector:@selector(actionIdentifier)] ||
      ![response respondsToSelector:@selector(notification)]) {
    return nil;
  }

  NSMutableDictionary* result = [[NSMutableDictionary alloc] init];
  result[@"actionIdentifier"] = response.actionIdentifier;
  result[@"date"] = @(response.notification.date.timeIntervalSince1970);
  result[@"identifier"] = response.notification.request.identifier;
  result[@"userInfo"] = response.notification.request.content.userInfo;

  // [response isKindOfClass:[UNTextInputNotificationResponse class]]
  if ([response respondsToSelector:@selector(userText)]) {
    result[@"userText"] =
        static_cast<UNTextInputNotificationResponse*>(response).userText;
  }

  return result;
}

@implementation ElectronApplicationDelegate

- (void)applicationDidFinishLaunching:(NSNotification*)notify {
  NSLog(@"applicationDidFinishLaunching");

  NSObject* user_notification =
      [notify userInfo][NSApplicationLaunchUserNotificationKey];
  NSDictionary* notification_info = nil;

  if (user_notification) {
    if ([user_notification isKindOfClass:[NSUserNotification class]]) {
      notification_info =
          [static_cast<NSUserNotification*>(user_notification) userInfo];
    } else if (@available(macOS 10.14, *)) {
      notification_info = UNNotificationResponseToNSDictionary(
          static_cast<UNNotificationResponse*>(user_notification));
    }
  }

  electron::Browser::Get()->DidFinishLaunching(
      electron::NSDictionaryToDictionaryValue(notification_info));
}

// - (void)setApplicationDockMenu:(electron::ElectronMenuModel*)model {
//   menu_controller_.reset([[ElectronMenuController alloc] initWithModel:model
//                                                  useDefaultAccelerator:NO]);
// }

@end