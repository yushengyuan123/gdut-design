// Copyright (c) 2013 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "shell/browser/browser.h"

#include <memory>
#include <string>
#include <utility>

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
}