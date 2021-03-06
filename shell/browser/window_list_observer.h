// Copyright (c) 2013 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef ELECTRON_SHELL_BROWSER_WINDOW_LIST_OBSERVER_H_
#define ELECTRON_SHELL_BROWSER_WINDOW_LIST_OBSERVER_H_

#include "base/observer_list_types.h"

// todo 有一个十分神奇的地方，这个OnWindowAdded没有看到有人类实现它
namespace electron {

class NativeWindow;

// 在browser.cc中实施了这个类，并且对下面的方法进行了实现
class WindowListObserver : public base::CheckedObserver {
 public:
  // Called immediately after a window is added to the list.
  virtual void OnWindowAdded(NativeWindow* window) {}

  // Called immediately after a window is removed from the list.
  virtual void OnWindowRemoved(NativeWindow* window) {}

  // Called when a window close is cancelled by beforeunload handler.
  virtual void OnWindowCloseCancelled(NativeWindow* window) {}

  // Called immediately after all windows are closed.
  virtual void OnWindowAllClosed() {}

 protected:
  ~WindowListObserver() override {}
};

}  // namespace electron

#endif  // ELECTRON_SHELL_BROWSER_WINDOW_LIST_OBSERVER_H_
