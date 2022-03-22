#ifndef ELECTRON_SHELL_BROWSER_API_ELECTRON_API_WEB_CONTENTS_H_
#define ELECTRON_SHELL_BROWSER_API_ELECTRON_API_WEB_CONTENTS_H_

#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "base/observer_list_types.h"
#include "chrome/browser/devtools/devtools_eye_dropper.h"
#include "chrome/browser/devtools/devtools_file_system_indexer.h"
#include "chrome/browser/ui/exclusive_access/exclusive_access_context.h"  // nogncheck
#include "content/common/cursors/webcursor.h"
#include "content/common/frame.mojom.h"
#include "content/public/browser/devtools_agent_host.h"
#include "content/public/browser/keyboard_event_processing_result.h"
#include "content/public/browser/permission_type.h"
#include "content/public/browser/render_widget_host.h"
#include "content/public/browser/web_contents.h"
#include "content/public/browser/web_contents_delegate.h"
#include "content/public/browser/web_contents_observer.h"
#include "gin/handle.h"
#include "gin/wrappable.h"

#include "shell/browser/ui/inspectable_web_contents.h"

namespace gin_helper {
class Dictionary;
}

namespace gin {
class Arguments;
}

namespace electron {
class ElectronBrowserContext;
class InspectableWebContents;
class NativeWindow;

namespace api {
class WebContents : public gin::Wrappable<WebContents>,
                    public content::WebContentsObserver {
 public:
  enum class Type {
    kBackgroundPage,  // An extension background page.
    kBrowserWindow,   // Used by BrowserWindow.
    kBrowserView,     // Used by BrowserView.
    kRemote,          // Thin wrap around an existing WebContents.
    kWebView,         // Used by <webview>.
    kOffScreen,       // Used for offscreen rendering
  };

  static gin::WrapperInfo kWrapperInfo;

  // Create a new WebContents and return the V8 wrapper of it.
  static gin::Handle<WebContents> New(v8::Isolate* isolate,
                                      const gin_helper::Dictionary& options);

  static gin::Handle<WebContents> CreateFromWebPreferences(
      v8::Isolate* isolate,
      const gin_helper::Dictionary& web_preferences);

  ~WebContents() override;    

  bool IsGuest() const;

  base::WeakPtr<WebContents> GetWeakPtr() { return weak_factory_.GetWeakPtr(); }

  void SetOwnerWindow(NativeWindow* owner_window);

  void SetOwnerWindow(content::WebContents* web_contents,
                      NativeWindow* owner_window);

  void LoadURL(const GURL& url, const gin_helper::Dictionary& options);                    

  void InitWithSessionAndOptions(
      v8::Isolate* isolate,
      std::unique_ptr<content::WebContents> web_contents,
      gin::Handle<class Session> session,
      const gin_helper::Dictionary& options);

  // Creates a InspectableWebContents object and takes ownership of
  // |web_contents|.
  void InitWithWebContents(std::unique_ptr<content::WebContents> web_contents,
                           ElectronBrowserContext* browser_context,
                           bool is_guest);      
              
  // Returns the WebContents managed by this delegate.
  content::WebContents* GetWebContents() const;

  InspectableWebContents* inspectable_web_contents() const {
    return inspectable_web_contents_.get();
  }                           

 private:
  base::WeakPtr<NativeWindow> owner_window_;

  // Creates a new content::WebContents.
  WebContents(v8::Isolate* isolate, const gin_helper::Dictionary& options);

  std::unique_ptr<InspectableWebContents> inspectable_web_contents_;

  bool enable_devtools_ = true;

  Type type_ = Type::kBrowserWindow;

  ElectronBrowserContext* browser_context_;

  base::WeakPtrFactory<WebContents> weak_factory_{this};
};

}  // namespace api
}  // namespace electron

#endif