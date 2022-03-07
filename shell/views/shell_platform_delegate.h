#ifndef CONTENT_SHELL_BROWSER_SHELL_PLATFORM_DELEGATE_H_
#define CONTENT_SHELL_BROWSER_SHELL_PLATFORM_DELEGATE_H_

#include <memory>
#include <string>


#include "base/containers/flat_map.h"
#include "content/public/browser/web_contents.h"
#include "shell/views/shell.h"

class GURL;

namespace electron {
  class Shell;

  class ShellPlatformDelegate {
    public:
      ShellPlatformDelegate();
      virtual ~ShellPlatformDelegate();

      // Called after creating a Shell instance, with its initial size.
      virtual void CreatePlatformWindow(Shell* shell);

      virtual void SetContents(Shell* shell);

    private:
      struct ShellData;

      base::flat_map<Shell*, ShellData> shell_data_map_;  
  };
}


#endif