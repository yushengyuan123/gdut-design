#ifndef ELECTRON_SHELL_BROWSER_BROWSER_H_
#define ELECTRON_SHELL_BROWSER_BROWSER_H_

#include <memory>
#include <string>
#include <vector>

#include "base/observer_list.h"

namespace electron {
  class Browser : public WindowListObserver {
    public:
      Browser();
      ~Browser() override;  

      // disable copy
      Browser(const Browser&) = delete;
      Browser& operator=(const Browser&) = delete;  


    private:
      // Observers of the browser.
      base::ObserverList<BrowserObserver> observers_;        
  }
}


#endif  // ELECTRON_SHELL_BROWSER_BROWSER_H_