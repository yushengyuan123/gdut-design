// Copyright (c) 2013 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef ELECTRON_SHELL_BROWSER_NATIVE_WINDOW_H_
#define ELECTRON_SHELL_BROWSER_NATIVE_WINDOW_H_

#include <list>
#include <memory>
#include <string>
#include <vector>

#include "base/observer_list.h"
#include "shell/browser/native_window_observer.h"

namespace electron {
  
}

class NativeWindow {
  private:
    // Observers of this window.
    base::ObserverList<NativeWindowObserver> observers_;
  public:
    ~NativeWindow() override;

    // disable copy
    NativeWindow(const NativeWindow&) = delete;
    NativeWindow& operator=(const NativeWindow&) = delete;

    void NotifyWindowShow();
};



#endif