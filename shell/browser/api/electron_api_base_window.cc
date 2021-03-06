#include "shell/browser/api/electron_api_base_window.h"

#include <string>
#include <utility>
#include <vector>

#include "gin/dictionary.h"
#include "shell/common/gin_helper/dictionary.h"

namespace electron {
namespace api {
BaseWindow::BaseWindow(v8::Isolate* isolate,
                       const gin_helper::Dictionary& options) {
  gin::Handle<BaseWindow> parent;
  window_.reset(NativeWindow::Create(options, nullptr));
  // window_->AddObserver(this);
}

BaseWindow::BaseWindow(gin_helper::Arguments* args,
                       const gin_helper::Dictionary& options)
    : BaseWindow(args->isolate(), options) {}

BaseWindow::~BaseWindow() {}
}  // namespace api
}  // namespace electron