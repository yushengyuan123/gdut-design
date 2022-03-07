
#ifndef CONTENT_SHELL_BROWSER_SHELL_H_
#define CONTENT_SHELL_BROWSER_SHELL_H_

#include <stdint.h>

#include <memory>
#include <utility>
#include <vector>

#include "content/public/browser/web_contents_delegate.h"
#include "content/public/browser/web_contents.h"
#include "shell/views/shell_browser_context.h"


class GURL;

namespace content {
class WebContents;
class SiteInstance;
class WebContentsDelegate;
class BrowserContext;
}

namespace electron {
  class ShellBrowserContext;
  class ShellPlatformDelegate;

  class Shell : public content::WebContentsDelegate {
    public:
      ~Shell() override;

      void LoadURL(const GURL& url);

      void LoadURLForFrame(const GURL& url,
                          const std::string& frame_name,
                          ui::PageTransition);

      content::WebContents* web_contents() const { return web_contents_.get(); }

      static void Initialize(std::unique_ptr<ShellPlatformDelegate> platform);

      static Shell* CreateNewWindow(
        content::BrowserContext* browser_context,
        const GURL& url,
        const scoped_refptr<content::SiteInstance>& site_instance);

    private:
      Shell(std::unique_ptr<content::WebContents> web_contents);

      // Helper to create a new Shell given a newly created WebContents.
      static Shell* CreateShell(std::unique_ptr<content::WebContents> web_contents);

      std::unique_ptr<content::WebContents> web_contents_;  
  };
}



#endif