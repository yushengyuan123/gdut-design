#ifndef ELECTRON_SHELL_BROWSER_API_ELECTRON_API_BROWSER_WINDOW_H_
#define ELECTRON_SHELL_BROWSER_API_ELECTRON_API_BROWSER_WINDOW_H_

#include <string>
#include <vector>

#include "gin/wrappable.h"

#include "shell/browser/api/electron_api_base_window.h"
#include "shell/browser/api/electron_api_web_contents.h"
#include "shell/browser/ui/inspectable_web_contents_view.h"
#include "shell/common/gin_helper/dictionary.h"
#include "shell/common/gin_helper/wrappable.h"
#include "shell/common/gin_helper/wrappable_base.h"

namespace electron {
namespace api {
class BrowserWindow : public BaseWindow,
                      public content::RenderWidgetHost::InputEventObserver,
                      public content::WebContentsObserver {
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

  v8::Local<v8::Value> GetWebContents(v8::Isolate* isolate);
  

 private:
  void OverrideNSWindowContentView(InspectableWebContentsView* webView);

  v8::Global<v8::Value> web_contents_;

  base::WeakPtr<api::WebContents> api_web_contents_;
};
}  // namespace api
}  // namespace electron

#endif