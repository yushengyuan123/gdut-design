#include "shell/browser/api/electron_api_app.h"

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "base/callback_helpers.h"
#include "base/command_line.h"
#include "base/containers/span.h"
#include "base/environment.h"
#include "base/files/file_path.h"
#include "base/files/file_util.h"
#include "base/no_destructor.h"
#include "base/path_service.h"
#include "base/system/sys_info.h"
#include "base/values.h"
#include "gin/handle.h"

#include "shell/common/gin_helper/dictionary.h"
#include "shell/common/node_includes.h"

#include "stdio.h"

namespace electron {
namespace api {

gin::WrapperInfo App::kWrapperInfo = {gin::kEmbedderNativeGin};

App::App() {
  Browser::Get()->AddObserver(this);
}

App::~App() {}

const char* App::GetTypeName() {
  return "App";
}

// static
App* App::Get() {
  static base::NoDestructor<App> app;
  return app.get();
}

// static
gin::Handle<App> App::Create(v8::Isolate* isolate) {
  return gin::CreateHandle(isolate, Get());
}

gin::ObjectTemplateBuilder App::GetObjectTemplateBuilder(v8::Isolate* isolate) {
  auto browser = base::Unretained(Browser::Get());

  return gin_helper::EventEmitterMixin<App>::GetObjectTemplateBuilder(isolate)
      .SetMethod("whenReady",
                 base::BindRepeating(&Browser::WhenReady, browser));
}
}  // namespace api
}  // namespace electron

namespace {
// 这个需要处理一个关键的问题，你需要向v8这个exports对象塞进入你的接口
// 所以就需要用到这个gin_helper
void Initialize(v8::Local<v8::Object> exports,
                v8::Local<v8::Value> unused,
                v8::Local<v8::Context> context,
                void* priv) {
  v8::Isolate* isolate = context->GetIsolate();
  gin_helper::Dictionary dict(isolate, exports);
  dict.Set("app", electron::api::App::Create(isolate));
}
}  // namespace

NODE_LINKED_MODULE_CONTEXT_AWARE(electron_browser_app, Initialize)