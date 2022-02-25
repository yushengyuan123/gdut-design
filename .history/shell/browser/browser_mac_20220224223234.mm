#include "shell/browser/browser.h"

#include <memory>
#include <string>
#include <utility>


namespace electron {

  namespace {}

  void Browser::Show() {
    [[AtomApplication sharedApplication] unhide:nil];
  }
}