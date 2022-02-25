// Copyright (c) 2013 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef ELECTRON_SHELL_BROWSER_BROWSER_OBSERVER_H_
#define ELECTRON_SHELL_BROWSER_BROWSER_OBSERVER_H_

#include <string>

#include "base/observer_list_types.h"

namespace electron {
  class BrowserObserver : public base::CheckedObserver {
    public:
      // The browser is about to close all windows.
      virtual void OnBeforeQuit(bool* prevent_default) {}

    protected:
      ~BrowserObserver() override {}

        // The browser is quitting.
      virtual void OnQuit() {}

  };
}


#endif