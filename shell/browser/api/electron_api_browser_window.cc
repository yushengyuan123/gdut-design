#include "shell/browser/api/electron_api_browser_window.h"
#include "stdio.h"

#include "base/threading/thread_task_runner_handle.h"
#include "content/browser/renderer_host/render_widget_host_impl.h"  // nogncheck
#include "content/browser/renderer_host/render_widget_host_owner_delegate.h"  // nogncheck
#include "content/browser/web_contents/web_contents_impl.h"  // nogncheck
#include "content/public/browser/render_process_host.h"
#include "content/public/browser/render_view_host.h"

#include "shell/browser/api/electron_api_web_contents.h"
#include "shell/browser/api/electron_api_web_contents_view.h"
#include "shell/browser/browser.h"
#include "shell/common/color_util.h"
#include "shell/common/gin_helper/constructor.h"
#include "shell/common/gin_helper/dictionary.h"
#include "shell/common/gin_helper/object_template_builder.h"
#include "shell/common/gin_helper/wrappable_base.h"
#include "shell/common/options_switches.h"
#include "shell/common/node_includes.h"


namespace electron {
namespace api {
BrowserWindow::BrowserWindow(gin::Arguments* args,
                             const gin_helper::Dictionary& options)
  : BaseWindow(args->isolate(), options) {
  printf("01111\n");   
  v8::Isolate* isolate = args->isolate();

  printf("01\n");   
  gin_helper::Dictionary web_preferences =
      gin::Dictionary::CreateEmpty(isolate);
  options.Get(options::kWebPreferences, &web_preferences);

  bool transparent = false;
  options.Get(options::kTransparent, &transparent);

  std::string vibrancy_type;
#if defined(OS_MAC)
  options.Get(options::kVibrancyType, &vibrancy_type);
#endif  

  // Copy the backgroundColor to webContents.
  std::string color;
  if (options.Get(options::kBackgroundColor, &color)) {
    web_preferences.SetHidden(options::kBackgroundColor, color);
  } else if (!vibrancy_type.empty() || transparent) {
    // If the BrowserWindow is transparent or a vibrancy type has been set,
    // also propagate transparency to the WebContents unless a separate
    // backgroundColor has been set.
    web_preferences.SetHidden(options::kBackgroundColor,
                              ToRGBAHex(SK_ColorTRANSPARENT));
  }


  // Copy the show setting to webContents, but only if we don't want to paint
  // when initially hidden
  bool paint_when_initially_hidden = true;
  options.Get("paintWhenInitiallyHidden", &paint_when_initially_hidden);
  if (!paint_when_initially_hidden) {
    bool show = true;
    options.Get(options::kShow, &show);
    web_preferences.Set(options::kShow, show);
  }

  bool titleBarOverlay = false;
  options.Get(options::ktitleBarOverlay, &titleBarOverlay);
  if (titleBarOverlay) {
    std::string enabled_features = "";
    if (web_preferences.Get(options::kEnableBlinkFeatures, &enabled_features)) {
      enabled_features += ",";
    }
    enabled_features += features::kWebAppWindowControlsOverlay.name;
    web_preferences.Set(options::kEnableBlinkFeatures, enabled_features);
  }  

  v8::Local<v8::Value> value;
  if (options.Get("webContents", &value)) {
    web_preferences.SetHidden("webContents", value);
  }    

  // Creates the WebContentsView.
  gin::Handle<WebContentsView> web_contents_view =
      WebContentsView::Create(isolate, web_preferences);

  DCHECK(web_contents_view.get());       

  gin::Handle<WebContents> web_contents =
      web_contents_view->GetWebContents(isolate);

  web_contents_.Reset(isolate, web_contents.ToV8()); 
  // api_web_contents_ = web_contents->GetWeakPtr();  

  // web_contents->SetOwnerWindow(window());

  // 这句话比较关键，这句话内部调用了SetAlignedPointerInInternalField方法，没有这句话
  // 在你的下面那些SetProperty是无效的
  InitWithArgs(args);

  OverrideNSWindowContentView(
      web_contents->inspectable_web_contents()->GetView()); 

}

BrowserWindow::~BrowserWindow() {

}   

gin_helper::WrappableBase* BrowserWindow::New(gin_helper::ErrorThrower thrower,
                                              gin::Arguments* args) {                                            
  if (!Browser::Get()->is_ready()) { 
    thrower.ThrowError("Cannot create BrowserWindow before app is ready");
    return nullptr;
  }

  // if (args->Length() > 1) {
  //   args->ThrowError();
  //   return nullptr;
  // }

  gin_helper::Dictionary options;
  options = gin::Dictionary::CreateEmpty(args->isolate());
  // if (!(args->Length() == 1 && args->GetNext(&options))) {
  //   options = gin::Dictionary::CreateEmpty(args->isolate());
  // }
  return new BrowserWindow(args, options);
}

v8::Local<v8::Value> BrowserWindow::GetWebContents(v8::Isolate* isolate) {
  if (web_contents_.IsEmpty())
    return v8::Null(isolate);
  printf("caoniamne11\n");  
  return v8::Local<v8::Value>::New(isolate, web_contents_);
}


// static
void BrowserWindow::BuildPrototype(v8::Isolate* isolate,
                                   v8::Local<v8::FunctionTemplate> prototype) {
  prototype->SetClassName(gin::StringToV8(isolate, "BrowserWindow"));
  gin_helper::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
    .SetProperty("webContents", &BrowserWindow::GetWebContents);
}

}  // namespace api
}  // namespace electron

namespace {

// v8::Local<v8::Value> sayHello(v8::Isolate* isolate) {
//   printf("heello\n");
//   if (electron::api::BrowserWindow::web_contents_.IsEmpty()) {
//     printf("null\n");
//     return v8::Null(isolate);
//   }
//   return v8::Local<v8::Value>::New(isolate, electron::api::BrowserWindow::web_contents_);
// }

using electron::api::BrowserWindow;

void Initialize(v8::Local<v8::Object> exports,
                v8::Local<v8::Value> unused,
                v8::Local<v8::Context> context,
                void* priv) {
  v8::Isolate* isolate = context->GetIsolate();
  gin_helper::Dictionary dict(isolate, exports);

  dict.Set("BrowserWindow", gin_helper::CreateConstructor<BrowserWindow>(
               isolate, base::BindRepeating(&BrowserWindow::New)));
  // dict.SetMethod("showSaveDialog", &BrowserWindow::GetWebContents);
}

}  // namespace

NODE_LINKED_MODULE_CONTEXT_AWARE(electron_browser_window, Initialize)
