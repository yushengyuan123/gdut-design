#ifndef CONTENT_SHELL_BROWSER_SHELL_PLATFORM_DELEGATE_H_
#define CONTENT_SHELL_BROWSER_SHELL_PLATFORM_DELEGATE_H_

#include <memory>
#include <string>
#include "content/public/browser/web_contents.h"
#include "shell/browser/shell.h"

class GURL;

namespace electron {
  class Shell;

  class ShellPlatformDelegate {
    public:
      ShellPlatformDelegate();
      virtual ~ShellPlatformDelegate();

      // Called after creating a Shell instance, with its initial size.
      virtual void CreatePlatformWindow(Shell* shell);
  };
}


#endif