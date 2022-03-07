// Copyright (c) 2013 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef ELECTRON_SHELL_BROWSER_MAC_ELECTRON_APPLICATION_H_
#define ELECTRON_SHELL_BROWSER_MAC_ELECTRON_APPLICATION_H_

#include "base/callback.h"
#include "base/mac/scoped_nsobject.h"
#include "base/mac/scoped_sending_event.h"

#import <AppKit/AppKit.h>

@interface AtomApplication : NSApplication <CrAppProtocol,
                                            CrAppControlProtocol,
                                            NSUserActivityDelegate> {
  @private
    BOOL handlingSendEvent_;
    NSCondition* handoffLock_;
}

+ (AtomApplication*)sharedApplication;
- (void)registerURLHandler;

// CrAppProtocol:
- (BOOL)isHandlingSendEvent;

// CrAppControlProtocol:
- (void)setHandlingSendEvent:(BOOL)handlingSendEvent;

@end

#endif  // ELECTRON_SHELL_BROWSER_MAC_ELECTRON_APPLICATION_H_
