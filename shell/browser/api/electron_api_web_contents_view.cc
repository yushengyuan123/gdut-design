#include "shell/browser/api/electron_api_web_contents_view.h"

#include "base/no_destructor.h"
#include "shell/browser/api/electron_api_web_contents.h"
#include "shell/browser/ui/inspectable_web_contents.h"
#include "shell/browser/ui/inspectable_web_contents_view.h"
#include "shell/common/gin_helper/dictionary.h"
#include "shell/common/gin_helper/object_template_builder.h"
#include "shell/common/node_includes.h"

#if defined(OS_MAC)
#include "shell/browser/ui/cocoa/delayed_native_view_host.h"
#endif

namespace electron {

namespace api {
WebContentsView::WebContentsView(v8::Isolate* isolate,
                                 gin::Handle<WebContents> web_contents)
    : View(new DelayedNativeViewHost(
          web_contents->inspectable_web_contents()->GetView()->GetNativeView())),
          web_contents_(isolate, web_contents.ToV8()),
      api_web_contents_(web_contents.get()) {
  // Observe(web_contents->web_contents());
}

WebContentsView::~WebContentsView() {}

// static
gin::Handle<WebContentsView> WebContentsView::Create(
    v8::Isolate* isolate,
    const gin_helper::Dictionary& web_preferences) {
  v8::Local<v8::Context> context = isolate->GetCurrentContext();
  v8::Local<v8::Value> arg = gin::ConvertToV8(isolate, web_preferences);
  v8::Local<v8::Object> obj;
 
  // 这个NewInstance会调用到下面的New函数
  if (GetConstructor(isolate)->NewInstance(context, 1, &arg).ToLocal(&obj)) {
    gin::Handle<WebContentsView> web_contents_view;
    if (gin::ConvertFromV8(isolate, obj, &web_contents_view))
      return web_contents_view;
  }
  return gin::Handle<WebContentsView>();
}

// static
v8::Local<v8::Function> WebContentsView::GetConstructor(v8::Isolate* isolate) {
  static base::NoDestructor<v8::Global<v8::Function>> constructor;
  // if (constructor.get()->IsEmpty()) {
  //   constructor->Reset(
  //       isolate, gin_helper::CreateConstructor<WebContentsView>(
  //                    isolate, base::BindRepeating(&WebContentsView::New)));
  // }
  constructor->Reset(
        isolate, gin_helper::CreateConstructor<WebContentsView>(
                     isolate, base::BindRepeating(&WebContentsView::New)));
  return v8::Local<v8::Function>::New(isolate, *constructor.get());
}

// static
gin_helper::WrappableBase* WebContentsView::New(
    gin_helper::Arguments* args,
    const gin_helper::Dictionary& web_preferences) {
  // 这里创建出来一个web_contents
  auto web_contents =
      WebContents::CreateFromWebPreferences(args->isolate(), web_preferences);
  // Constructor call.
  auto* view = new WebContentsView(args->isolate(), web_contents);
  view->InitWithArgs(args);
  return view;
}

// static
void WebContentsView::BuildPrototype(
    v8::Isolate* isolate,
    v8::Local<v8::FunctionTemplate> prototype) {
  prototype->SetClassName(gin::StringToV8(isolate, "WebContentsView"));
  gin_helper::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
      .SetProperty("webContents", &WebContentsView::GetWebContents);
}

gin::Handle<WebContents> WebContentsView::GetWebContents(v8::Isolate* isolate) {
  if (!api_web_contents_) {
    printf("sssss\n");
  }


  return gin::CreateHandle(isolate, api_web_contents_);
}
}  // namespace api


}  // namespace electron

namespace {

using electron::api::WebContentsView;

void Initialize(v8::Local<v8::Object> exports,
                v8::Local<v8::Value> unused,
                v8::Local<v8::Context> context,
                void* priv) {
  v8::Isolate* isolate = context->GetIsolate();
  gin_helper::Dictionary dict(isolate, exports);
  dict.Set("WebContentsView", WebContentsView::GetConstructor(isolate));
}

}  // namespace

NODE_LINKED_MODULE_CONTEXT_AWARE(electron_browser_web_contents_view, Initialize)