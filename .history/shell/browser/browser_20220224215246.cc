// Copyright (c) 2013 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "shell/browser/browser.h"

#include <memory>
#include <string>
#include <utility>

#include "shell/browser/electron_browser_main_parts.h"
#include "shell/browser/window_list.h"

namespace electron {
  namespace {}

  Browser::Browser() {
    // 把这个Browser实例加入到WindowListObserver数组中
    WindowList::AddObserver(this);
  }

  Browser::~Browser() {
    WindowList::RemoveObserver(this);
  }

  void Browser::Quit() {
  if (is_quitting_)
    return;

  is_quitting_ = HandleBeforeQuit();
  if (!is_quitting_)
    return;

  if (electron::WindowList::IsEmpty())
    NotifyAndShutdown();
  else
    electron::WindowList::CloseAllWindows();
}

  // static
  Browser* Browser::Get() {
    return ElectronBrowserMainParts::Get()->browser();
  }
}