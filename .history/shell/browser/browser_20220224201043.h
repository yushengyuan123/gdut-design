#ifndef ELECTRON_SHELL_BROWSER_BROWSER_H_
#define ELECTRON_SHELL_BROWSER_BROWSER_H_

#include <memory>
#include <string>
#include <vector>

namespace electron {
  class Browser : public WindowListObserver {
    public:
      Browser();
      ~Browser() override;  

      // disable copy
      Browser(const Browser&) = delete;
      Browser& operator=(const Browser&) = delete;  


    private:
        
  }
}


#endif  // ELECTRON_SHELL_BROWSER_BROWSER_H_