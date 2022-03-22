
#ifndef ELECTRON_SHELL_BROWSER_API_ELECTRON_API_WEB_CONTENTS_VIEW_H_
#define ELECTRON_SHELL_BROWSER_API_ELECTRON_API_WEB_CONTENTS_VIEW_H_

#include "content/public/browser/web_contents_observer.h"
#include "shell/browser/api/electron_api_view.h"
#include "shell/browser/ui/inspectable_web_contents.h"

namespace gin_helper {
class Dictionary;
}

namespace electron {
namespace api {
class WebContents;

class WebContentsView : public View, public content::WebContentsObserver {
 public:
  static gin::Handle<WebContentsView> Create(
      v8::Isolate* isolate,
      const gin_helper::Dictionary& web_preferences);

  // Return the cached constructor function.
  static v8::Local<v8::Function> GetConstructor(v8::Isolate* isolate);

  // gin_helper::Wrappable
  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

  // Public APIs.
  gin::Handle<WebContents> GetWebContents(v8::Isolate* isolate);

  InspectableWebContents* inspectable_web_contents() const {
    return inspectable_web_contents_.get();
  }                           

 protected:
  WebContentsView(v8::Isolate* isolate, gin::Handle<WebContents> web_contents);
  ~WebContentsView() override;

 private:
  static gin_helper::WrappableBase* New(
      gin_helper::Arguments* args,
      const gin_helper::Dictionary& web_preferences);

  std::unique_ptr<InspectableWebContents> inspectable_web_contents_;

  v8::Global<v8::Value> web_contents_;

  api::WebContents* api_web_contents_;
};
}  // namespace api
}  // namespace electron

#endif