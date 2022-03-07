#include "shell/browser/shell.h"

#include <stddef.h>

#include <map>
#include <memory>
#include <string>
#include <utility>

#include "base/command_line.h"
#include "base/location.h"
#include "base/no_destructor.h"
#include "base/run_loop.h"
#include "base/strings/string_number_conversions.h"
#include "base/strings/string_util.h"
#include "base/strings/utf_string_conversions.h"
#include "base/task/single_thread_task_runner.h"
#include "base/threading/thread_task_runner_handle.h"
#include "content/public/browser/navigation_controller.h"
#include "content/public/browser/navigation_entry.h"
#include "content/public/browser/web_contents.h"

namespace electron {
  namespace {
    ShellPlatformDelegate* g_platform;
  }


  Shell::Shell(std::unique_ptr<content::WebContents> web_contents)
      : WebContentsObserver(web_contents.get()),
        web_contents_(std::move(web_contents)) {

  }

  Shell::~Shell() {

  }

  Shell* Shell::CreateShell(std::unique_ptr<content::WebContents> web_contents) {
    Shell* shell = new Shell(std::move(web_contents));
    // 这个方法不是定义在content/shell/browser/shell_platform_delegate.cc
    // 而是定义在了content/shell/browser/shell_platform_delegate_mac.mm
    g_platform->CreatePlatformWindow(shell);

    return shell;
  }


  Shell* Shell::CreateNewWindow(content::BrowserContext* browser_context,
                                const GURL& url,
                                const scoped_refptr<content::SiteInstance>& site_instance) {                             
    content::WebContents::CreateParams create_params(browser_context, site_instance);
    // if (base::CommandLine::ForCurrentProcess()->HasSwitch(
    //         switches::kForcePresentationReceiverForTesting)) {
    //   create_params.starting_sandbox_flags =
    //       content::kPresentationReceiverSandboxFlags;
    // }
    std::unique_ptr<content::WebContents> web_contents =
        content::WebContents::Create(create_params);
    Shell* shell =
        CreateShell(std::move(web_contents));
    // 这个loadUrl不支持字面上加载url那么简单，这么加载url的同时还启动了渲染进程
    if (!url.is_empty())
      shell->LoadURL(url);
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
    // LoadURLWithParams src/content/browser/renderer_host/navigation_controller_impl.cc
    web_contents_->GetController().LoadURLWithParams(params);
  }
}