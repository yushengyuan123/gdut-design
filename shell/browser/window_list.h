// Copyright (c) 2013 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef ELECTRON_SHELL_BROWSER_WINDOW_LIST_H_
#define ELECTRON_SHELL_BROWSER_WINDOW_LIST_H_

#include <vector>

#include "base/lazy_instance.h"
#include "base/observer_list.h"


namespace electron {

class NativeWindow;
class WindowListObserver;
// 这个东西应该对于每一个electron窗口的一个观察者对象
class WindowList {
 public:
  // disable copy
  WindowList(const WindowList&) = delete;
  WindowList& operator=(const WindowList&) = delete;

  typedef std::vector<NativeWindow*> WindowVector;


  // Adds or removes |window| from the list it is associated with.
  static void AddWindow(NativeWindow* window);
  static void RemoveWindow(NativeWindow* window);

 private:
  static WindowList* GetInstance();

  WindowList();
  ~WindowList();

  // A vector of the windows in this list, in the order they were added.
  WindowVector windows_;

  // A list of observers which will be notified of every window addition and
  // removal across all WindowLists.
  static base::LazyInstance<base::ObserverList<WindowListObserver>>::Leaky
      observers_;

  static WindowList* instance_;
};

}  // namespace electron

#endif  // ELECTRON_SHELL_BROWSER_WINDOW_LIST_H_
