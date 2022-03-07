
#ifndef ELECTRON_SHELL_BROWSER_API_ELECTRON_API_WEB_CONTENTS_VIEW_H_
#define ELECTRON_SHELL_BROWSER_API_ELECTRON_API_WEB_CONTENTS_VIEW_H_

#include "content/public/browser/web_contents_observer.h"
#include "shell/browser/api/electron_api_view.h"

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

 protected:
  WebContentsView(v8::Isolate* isolate, gin::Handle<WebContents> web_contents);
  ~WebContentsView() override;

 private:
  v8::Global<v8::Value> web_contents_;
  api::WebContents* api_web_contents_;
};
}  // namespace api
}  // namespace electron

#endif