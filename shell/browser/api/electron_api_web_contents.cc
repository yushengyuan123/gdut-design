#include "shell/browser/api/electron_api_web_contents.h"

#include <limits>
#include <memory>
#include <set>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "content/public/browser/site_instance.h"
#include "content/public/browser/web_contents.h"
#include "gin/arguments.h"
#include "gin/data_object_builder.h"
#include "gin/handle.h"
#include "gin/object_template_builder.h"
#include "gin/wrappable.h"

#include "shell/browser/api/electron_api_session.h"
#include "shell/browser/electron_browser_context.h"
#include "shell/browser/native_window.h"
#include "shell/browser/ui/inspectable_web_contents_view.h"
#include "shell/common/gin_helper/dictionary.h"
#include "shell/common/gin_helper/event_emitter_caller.h"
#include "shell/common/gin_helper/object_template_builder.h"
#include "shell/common/node_includes.h"

namespace gin {
template <>
struct Converter<electron::api::WebContents::Type> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   electron::api::WebContents::Type val) {
    using Type = electron::api::WebContents::Type;
    std::string type;
    switch (val) {
      case Type::kBackgroundPage:
        type = "backgroundPage";
        break;
      case Type::kBrowserWindow:
        type = "window";
        break;
      case Type::kBrowserView:
        type = "browserView";
        break;
      case Type::kRemote:
        type = "remote";
        break;
      case Type::kWebView:
        type = "webview";
        break;
      case Type::kOffScreen:
        type = "offscreen";
        break;
      default:
        break;
    }
    return gin::ConvertToV8(isolate, type);
  }

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     electron::api::WebContents::Type* out) {
    using Type = electron::api::WebContents::Type;
    std::string type;
    if (!ConvertFromV8(isolate, val, &type))
      return false;
    if (type == "backgroundPage") {
      *out = Type::kBackgroundPage;
    } else if (type == "browserView") {
      *out = Type::kBrowserView;
    } else if (type == "webview") {
      *out = Type::kWebView;
#if BUILDFLAG(ENABLE_OSR)
    } else if (type == "offscreen") {
      *out = Type::kOffScreen;
#endif
    } else {
      return false;
    }
    return true;
  }
};
}  // namespace gin

namespace electron {
namespace api {
namespace {}

WebContents::~WebContents() {}

bool WebContents::IsGuest() const {
  return type_ == Type::kWebView;
}

gin::WrapperInfo WebContents::kWrapperInfo = {gin::kEmbedderNativeGin};

WebContents::WebContents(v8::Isolate* isolate,
                         const gin_helper::Dictionary& options) {
  // Get type
  options.Get("type", &type_);

  // Whether to enable DevTools.
  options.Get("devTools", &enable_devtools_);

  std::unique_ptr<content::WebContents> web_contents;

  gin::Handle<api::Session> session = Session::FromPartition(isolate, "");

  content::WebContents::CreateParams params(session->browser_context());

  // params.initially_hidden = !initially_shown;
  web_contents = content::WebContents::Create(params);

  InitWithSessionAndOptions(isolate, std::move(web_contents), session, options);
}

void WebContents::SetOwnerWindow(NativeWindow* owner_window) {
  SetOwnerWindow(GetWebContents(), owner_window);
}

void WebContents::InitWithSessionAndOptions(
    v8::Isolate* isolate,
    std::unique_ptr<content::WebContents> owned_web_contents,
    gin::Handle<api::Session> session,
    const gin_helper::Dictionary& options) {
  InitWithWebContents(std::move(owned_web_contents), session->browser_context(),
                      IsGuest());
}

void WebContents::LoadURL(const GURL& url,
                          const gin_helper::Dictionary& options) {
                            printf("loadUrl\n");
  content::NavigationController::LoadURLParams params(url);
  web_contents()->GetController().LoadURLWithParams(params);
  printf("loadUrl ENd\n");
}

void WebContents::InitWithWebContents(
    std::unique_ptr<content::WebContents> web_contents,
    ElectronBrowserContext* browser_context,
    bool is_guest) {
  browser_context_ = browser_context;
  // web_contents->SetDelegate(this);

  // Determine whether the WebContents is offscreen.
  // auto* web_preferences = WebContentsPreferences::From(web_contents.get());
  // offscreen_ = web_preferences && web_preferences->IsOffscreen();

  // Create InspectableWebContents.
  inspectable_web_contents_ = std::make_unique<InspectableWebContents>(
      std::move(web_contents), is_guest);
  // inspectable_web_contents_->SetDelegate(this);
}

// static
gin::Handle<WebContents> WebContents::CreateFromWebPreferences(
    v8::Isolate* isolate,
    const gin_helper::Dictionary& web_preferences) {
  // Check if webPreferences has |webContents| option.
  gin::Handle<WebContents> web_contents;
  if (web_preferences.GetHidden("webContents", &web_contents) &&
      !web_contents.IsEmpty()) {
    printf("web_preferences.GetHidden\n");
  }

  web_contents = WebContents::New(isolate, web_preferences);

  return web_contents;
}

void WebContents::SetOwnerWindow(content::WebContents* web_contents,
                                 NativeWindow* owner_window) {
  if (owner_window) {
    owner_window_ = owner_window->GetWeakPtr();
    // NativeWindowRelay::CreateForWebContents(web_contents,
    //                                         owner_window->GetWeakPtr());
  } else {
    printf("owner_window null\n");
  }
}

content::WebContents* WebContents::GetWebContents() const {
  printf("GetWebContents\n");
  if (!inspectable_web_contents_) {
    printf("GetWebContents1\n");
    return nullptr;
  }
  printf("GetWebContents2\n");
  return inspectable_web_contents_->GetWebContents();
}

// static
gin::Handle<WebContents> WebContents::New(
    v8::Isolate* isolate,
    const gin_helper::Dictionary& options) {
  gin::Handle<WebContents> handle =
      gin::CreateHandle(isolate, new WebContents(isolate, options));
  v8::TryCatch try_catch(isolate);
  gin_helper::CallMethod(isolate, handle.get(), "_init");
  if (try_catch.HasCaught()) {
    node::errors::TriggerUncaughtException(isolate, try_catch);
  }
  return handle;
}
}  // namespace api

}  // namespace electron
