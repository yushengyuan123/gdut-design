#ifndef ELECTRON_SHELL_BROWSER_API_ELECTRON_API_BROWSER_WINDOW_H_
#define ELECTRON_SHELL_BROWSER_API_ELECTRON_API_BROWSER_WINDOW_H_

#include <string>
#include <vector>

#include "gin/wrappable.h"


#include "shell/browser/api/electron_api_base_window.h"
#include "shell/common/gin_helper/dictionary.h"
#include "shell/common/gin_helper/wrappable_base.h"
#include "shell/common/gin_helper/wrappable.h"

namespace electron {
namespace api {
class BrowserWindow : public BaseWindow,
                      public gin_helper::Wrappable<BrowserWindow> {
 public:
  static gin_helper::WrappableBase* New(gin_helper::ErrorThrower thrower,
                                        gin::Arguments* args);

  // disable copy
  BrowserWindow(const BrowserWindow&) = delete;
  BrowserWindow& operator=(const BrowserWindow&) = delete;

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

 protected:
  BrowserWindow(gin::Arguments* args, const gin_helper::Dictionary& options);
  ~BrowserWindow() override;
};
}  // namespace api
}  // namespace electron

#endif