#include "shell/browser/browser.h"

#include <memory>
#include <string>
#include <utility>

#include "shell/browser/mac/electron_application.h"
#include "shell/browser/mac/electron_application_delegate.h"


namespace electron {

  namespace {}

  void Browser::Show() {
    [[AtomApplication sharedApplication] unhide:nil];
  }

  void Browser::DockSetMenu(ElectronMenuModel* model) {
    ElectronApplicationDelegate* delegate =
        (ElectronApplicationDelegate*)[NSApp delegate];
    [delegate setApplicationDockMenu:model];
  }
}