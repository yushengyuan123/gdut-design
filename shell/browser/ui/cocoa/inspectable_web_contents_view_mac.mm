// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Copyright (c) 2013 Adam Roben <adam@roben.org>. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE-CHROMIUM file.

#include "shell/browser/ui/inspectable_web_contents_view_mac.h"

#import <AppKit/AppKit.h>

#include "base/strings/sys_string_conversions.h"
#import "shell/browser/ui/cocoa/electron_inspectable_web_contents_view.h"
#include "shell/browser/ui/inspectable_web_contents.h"


namespace electron {
  InspectableWebContentsView* CreateInspectableContentsView(
      InspectableWebContents* inspectable_web_contents) {
    return new InspectableWebContentsViewMac(inspectable_web_contents);
  }


  InspectableWebContentsViewMac::InspectableWebContentsViewMac(
      InspectableWebContents* inspectable_web_contents)
      : inspectable_web_contents_(inspectable_web_contents),
        view_([[ElectronInspectableWebContentsView alloc]
            initWithInspectableWebContentsViewMac:this]) {}

  InspectableWebContentsViewMac::~InspectableWebContentsViewMac() {
    
  }

  // 返回一个一个ElectronInspectableWebContentsView
  gfx::NativeView InspectableWebContentsViewMac::GetNativeView() const {
    return view_.get();
  }
}

}  // namespace electron
