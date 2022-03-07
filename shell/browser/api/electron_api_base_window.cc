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
      // The parent window.
      gin::Handle<BaseWindow> parent;
      // if (options.Get("parent", &parent) && !parent.IsEmpty())
      //   parent_window_.Reset(isolate, parent.ToV8());


      // Creates NativeWindow.
      window_.reset(NativeWindow::Create(
          options, parent.IsEmpty() ? nullptr : parent->window_.get()));
      window_->AddObserver(this);
    }   

    BaseWindow::BaseWindow(gin_helper::Arguments* args,
                          const gin_helper::Dictionary& options)
        : BaseWindow(args->isolate(), options) {

    }

    BaseWindow::~BaseWindow() {
 
    }
  }
}