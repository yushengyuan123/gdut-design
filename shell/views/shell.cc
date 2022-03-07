#include "shell/views/shell.h"

#include "content/public/browser/web_contents.h"
#include "content/public/browser/browser_context.h"
#include "shell/views/shell_browser_context.h"
#include "shell/views/shell_platform_delegate.h"

namespace electron {
  namespace {
    ShellPlatformDelegate* g_platform;
  }

  Shell::Shell(std::unique_ptr<content::WebContents> web_contents)
        :web_contents_(std::move(web_contents)) {

  }

  Shell::~Shell() {

  }

  // static
  Shell* Shell::CreateNewWindow(content::BrowserContext* browser_context,
                                const GURL& url,
                                const scoped_refptr<content::SiteInstance>& site_instance) {
    content::WebContents::CreateParams create_params(browser_context, site_instance);

    std::unique_ptr<content::WebContents> web_contents =
        content::WebContents::Create(create_params);
    Shell* shell = CreateShell(std::move(web_contents));

    if (!url.is_empty())
      shell->LoadURL(url);

    return shell;
  }

  // static
  void Shell::Initialize(std::unique_ptr<ShellPlatformDelegate> platform) {
    g_platform = platform.release();
  }

  Shell* Shell::CreateShell(std::unique_ptr<content::WebContents> web_contents) {
    Shell* shell = new Shell(std::move(web_contents));

    g_platform->CreatePlatformWindow(shell);

    g_platform->SetContents(shell);

    return shell;
  }

  void Shell::LoadURL(const GURL& url) {
    LoadURLForFrame(
          url, std::string(),
          ui::PageTransitionFromInt(ui::PAGE_TRANSITION_TYPED |
                                    ui::PAGE_TRANSITION_FROM_ADDRESS_BAR));
  }

  void Shell::LoadURLForFrame(const GURL& url,
                              const std::string& frame_name,
                              ui::PageTransition transition_type) {
    content::NavigationController::LoadURLParams params(url);
    params.frame_name = frame_name;
    params.transition_type = transition_type;
    web_contents_->GetController().LoadURLWithParams(params);
  }
}