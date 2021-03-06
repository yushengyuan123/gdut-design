// Copyright (c) 2013 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef ELECTRON_SHELL_BROWSER_NATIVE_WINDOW_OBSERVER_H_
#define ELECTRON_SHELL_BROWSER_NATIVE_WINDOW_OBSERVER_H_

#include <string>

#include "base/observer_list_types.h"

namespace electron {
  class NativeWindowObserver : public base::CheckedObserver {
    public:
      ~NativeWindowObserver() override {}

      // Called when window is shown.
      virtual void OnWindowShow() {}
  };
}

#endif