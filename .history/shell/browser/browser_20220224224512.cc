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

  void Browser::Shutdown() {
    if (is_shutdown_)
      return;

    is_shutdown_ = true;
    is_quitting_ = true;

    for (BrowserObserver& observer : observers_)
      observer.OnQuit();

    // 暂时不知道这些代码有什么用
    // if (quit_main_message_loop_) {
    //   // RunQuitClosure(std::move(quit_main_message_loop_));
    // } else {
    //   // There is no message loop available so we are in early stage, wait until
    //   // the quit_main_message_loop_ is available.
    //   // Exiting now would leave defunct processes behind.
    // }
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

  void Browser::NotifyAndShutdown() {
    if (is_shutdown_)
      return;

    bool prevent_default = false;
    for (BrowserObserver& observer : observers_)
      observer.OnWillQuit(&prevent_default);

    if (prevent_default) {
      is_quitting_ = false;
      return;
    }

    Shutdown();
  }

  bool Browser::HandleBeforeQuit() {
    bool prevent_default = false;
    for (BrowserObserver& observer : observers_)
      observer.OnBeforeQuit(&prevent_default);

    return !prevent_default;
  }

  void Browser::PreMainMessageLoopRun() {
    for (BrowserObserver& observer : observers_) {
      observer.OnPreMainMessageLoopRun();
    }
  }

  // static
  Browser* Browser::Get() {
    return ElectronBrowserMainParts::Get()->browser();
  }
}