#include "shell/browser/api/electron_api_browser_window.h"

#include "base/threading/thread_task_runner_handle.h"
#include "content/browser/renderer_host/render_widget_host_impl.h"  // nogncheck
#include "content/browser/renderer_host/render_widget_host_owner_delegate.h"  // nogncheck
#include "content/browser/web_contents/web_contents_impl.h"  // nogncheck
#include "content/public/browser/render_process_host.h"
#include "content/public/browser/render_view_host.h"
// #include "shell/browser/api/electron_api_web_contents_view.h"
#include "shell/common/gin_helper/arguments.h"
#include "shell/common/gin_helper/dictionary.h"


namespace electron {
  namespace api {
    BrowserWindow::BrowserWindow(gin::Arguments* args,
                                const gin_helper::Dictionary& options) 
        : BaseWindow(args->isolate(), options) {
      // v8::Isolate* isolate = args->isolate();
      // gin_helper::Dictionary web_preferences = gin::Dictionary::CreateEmpty(isolate);   
      // // Creates the WebContentsView.
      // gin::Handle<WebContentsView> web_contents_view =
      //     WebContentsView::Create(isolate, web_preferences);

      // bool transparent = false;
      // options.Get(options::kTransparent, &transparent);

      // std::string vibrancy_type;
      // options.Get(options::kVibrancyType, &vibrancy_type);    

      // options.Get(options::kWebPreferences, &web_preferences);    
          
      // OverrideNSWindowContentView(web_contents->inspectable_web_contents()->GetView());
    }
  }
}