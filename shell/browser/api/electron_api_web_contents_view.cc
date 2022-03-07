#include "shell/browser/api/electron_api_web_contents_view.h"

#include "shell/browser/api/electron_api_web_contents.h"
#include "shell/common/gin_helper/dictionary.h"

namespace electron {

  namespace api {
    WebContentsView::WebContentsView(v8::Isolate* isolate,
                                    gin::Handle<WebContents> web_contents):
          web_contents_(isolate, web_contents.ToV8()),
          api_web_contents_(web_contents.get()) {

      Observe(web_contents->web_contents());
    }

    WebContentsView::~WebContentsView() {

    }

    // static
    gin::Handle<WebContentsView> WebContentsView::Create(
        v8::Isolate* isolate,
        const gin_helper::Dictionary& web_preferences) {
      v8::Local<v8::Context> context = isolate->GetCurrentContext();
      v8::Local<v8::Value> arg = gin::ConvertToV8(isolate, web_preferences);
      v8::Local<v8::Object> obj;
      // if (GetConstructor(isolate)->NewInstance(context, 1, &arg).ToLocal(&obj)) {
      //   gin::Handle<WebContentsView> web_contents_view;
      //   if (gin::ConvertFromV8(isolate, obj, &web_contents_view))
      //     return web_contents_view;
      // }
      return gin::Handle<WebContentsView>();
    }
  }

}