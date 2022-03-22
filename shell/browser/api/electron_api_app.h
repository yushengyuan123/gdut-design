#ifndef ELECTRON_SHELL_BROWSER_API_ELECTRON_API_APP_H_
#define ELECTRON_SHELL_BROWSER_API_ELECTRON_API_APP_H_

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "base/task/cancelable_task_tracker.h"
#include "chrome/browser/icon_manager.h"
#include "chrome/browser/process_singleton.h"
#include "content/public/browser/browser_child_process_observer.h"
#include "content/public/browser/gpu_data_manager_observer.h"
#include "content/public/browser/render_process_host.h"
#include "gin/handle.h"
#include "net/base/completion_once_callback.h"
#include "net/base/completion_repeating_callback.h"
#include "net/ssl/client_cert_identity.h"

#include "shell/browser/browser.h"
#include "shell/browser/browser_observer.h"
#include "shell/browser/event_emitter_mixin.h"
#include "shell/common/gin_helper/wrappable.h"
#include "shell/common/gin_helper/promise.h"



namespace electron {

namespace api {
class App : public gin::Wrappable<App>,
            public gin_helper::EventEmitterMixin<App>,
            public BrowserObserver {
 public:
  static gin::WrapperInfo kWrapperInfo;

  static gin::Handle<App> Create(v8::Isolate* isolate);

  static App* Get();

  gin::ObjectTemplateBuilder GetObjectTemplateBuilder(
      v8::Isolate* isolate) override;

  App();

  // disable copy
  App(const App&) = delete;
  App& operator=(const App&) = delete;

  const char* GetTypeName() override;

 private:
  ~App() override;
};
}  // namespace api
}  // namespace electron

#endif