#include "shell/browser/api/electron_api_app.h"

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "shell/common/node_includes.h"

#include "stdio.h"

namespace electron {
  namespace api {
    void HelloWorld() {
      printf("hello world! electron\n");
    }
  }
}

namespace {
  // 这个需要处理一个关键的问题，你需要向v8这个exports对象塞进入你的接口
  // 所以就需要用到这个gin_helper
  void Initialize(v8::Local<v8::Object> exports,
                  v8::Local<v8::Value> unused,
                  v8::Local<v8::Context> context,
                  void* priv) {
    printf("hello world! electron Initialize\n");
    v8::Local<v8::String> key = v8::String::NewFromUtf8Literal(context->GetIsolate(),"name");
    v8::Local<v8::String> name = v8::String::NewFromUtf8Literal(context->GetIsolate(), "tony");

    exports->Set(context, key, name).Check();
  }
} 


NODE_LINKED_MODULE_CONTEXT_AWARE(electron_browser_app, Initialize)