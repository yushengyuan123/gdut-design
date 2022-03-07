#ifndef ELECTRON_SHELL_BROWSER_API_ELECTRON_API_WEB_CONTENTS_H_
#define ELECTRON_SHELL_BROWSER_API_ELECTRON_API_WEB_CONTENTS_H_

#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "content/public/browser/web_contents.h"
#include "shell/browser/ui/inspectable_web_contents.h"
#include "shell/browser/ui/inspectable_web_contents_delegate.h"
#include "shell/browser/ui/inspectable_web_contents_view_delegate.h"

namespace gin_helper {
class Dictionary;
}

namespace gin {
class Arguments;
}

namespace electron {
class InspectableWebContents;
class NativeWindow;


namespace api {
  class WebContents : public WebContents {
    
  }
}
}

#endif