// Copyright (c) 2013 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef ELECTRON_SHELL_BROWSER_MAC_ELECTRON_APPLICATION_H_
#define ELECTRON_SHELL_BROWSER_MAC_ELECTRON_APPLICATION_H_

#import <AppKit/AppKit.h>

@interface AtomApplication : NSApplication {}

+ (AtomApplication*)sharedApplication;

@end

#endif  // ELECTRON_SHELL_BROWSER_MAC_ELECTRON_APPLICATION_H_
