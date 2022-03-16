#include "shell/browser/api/electron_api_browser_window.h"
#include "stdio.h"

#include "base/threading/thread_task_runner_handle.h"
#include "content/browser/renderer_host/render_widget_host_impl.h"  // nogncheck
#include "content/browser/renderer_host/render_widget_host_owner_delegate.h"  // nogncheck
#include "content/browser/web_contents/web_contents_impl.h"  // nogncheck
#include "content/public/browser/render_process_host.h"
#include "content/public/browser/render_view_host.h"
#include "shell/common/gin_helper/constructor.h"
#include "shell/common/gin_helper/dictionary.h"
#include "shell/common/gin_helper/wrappable_base.h"
#include "shell/common/node_includes.h"

namespace electron {
namespace api {
BrowserWindow::BrowserWindow(gin::Arguments* args,
                             const gin_helper::Dictionary& options)
  : BaseWindow(args->isolate(), options) {
  printf("调用BrowserWindow构造函数");
}

BrowserWindow::~BrowserWindow() {

}   

gin_helper::WrappableBase* BrowserWindow::New(gin_helper::ErrorThrower thrower,
                                              gin::Arguments* args) {
  // if (!Browser::Get()->is_ready()) {
  //   thrower.ThrowError("Cannot create BrowserWindow before app is ready");
  //   return nullptr;
  // }

  // if (args->Length() > 1) {
  //   args->ThrowError();
  //   return nullptr;
  // }

  gin_helper::Dictionary options;
  // if (!(args->Length() == 1 && args->GetNext(&options))) {
  //   options = gin::Dictionary::CreateEmpty(args->isolate());
  // }

  return new BrowserWindow(args, options);
}

// static
void BrowserWindow::BuildPrototype(v8::Isolate* isolate,
                                   v8::Local<v8::FunctionTemplate> prototype) {
  prototype->SetClassName(gin::StringToV8(isolate, "BrowserWindow"));
}

}  // namespace api
}  // namespace electron

namespace {

using electron::api::BrowserWindow;

void Initialize(v8::Local<v8::Object> exports,
                v8::Local<v8::Value> unused,
                v8::Local<v8::Context> context,
                void* priv) {
  v8::Isolate* isolate = context->GetIsolate();
  gin_helper::Dictionary dict(isolate, exports);
  dict.Set("BrowserWindow",
           gin_helper::CreateConstructor<BrowserWindow>(
               isolate, base::BindRepeating(&BrowserWindow::New)));
}

}  // namespace

NODE_LINKED_MODULE_CONTEXT_AWARE(electron_browser_window, Initialize)
