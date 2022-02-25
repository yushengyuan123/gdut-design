#ifndef ELECTRON_SHELL_BROWSER_ELECTRON_BROWSER_CLIENT_H_
#define ELECTRON_SHELL_BROWSER_ELECTRON_BROWSER_CLIENT_H_

#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>


namespace content {}

namespace net {}

namespace electron {
  class ElectronBrowserMainParts;

  class electron_browser_client
  {
  private:
    /* data */
  public:
    electron_browser_client(/* args */);
    ~electron_browser_client();
  };
  
  electron_browser_client::electron_browser_client(/* args */)
  {
  }
  
  electron_browser_client::~electron_browser_client()
  {
  }
  
}


#endif  // ELECTRON_SHELL_BROWSER_ELECTRON_BROWSER_CLIENT_H_