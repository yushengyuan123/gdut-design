#include "shell/browser/electron_browser_main_parts.h"

#include <memory>
#include <string>
#include <utility>

#include "base/base_switches.h"
#include "base/command_line.h"
#include "base/feature_list.h"
#include "base/metrics/field_trial.h"
#include "base/path_service.h"
#include "base/run_loop.h"
#include "base/strings/string_number_conversions.h"
#include "base/strings/utf_string_conversions.h"
#include "chrome/browser/icon_manager.h"
#include "components/os_crypt/os_crypt.h"
#include "content/browser/browser_main_loop.h"  // nogncheck
#include "content/public/browser/browser_thread.h"
#include "content/public/browser/child_process_security_policy.h"
#include "content/public/browser/device_service.h"
#include "content/public/browser/web_ui_controller_factory.h"
#include "content/public/common/content_features.h"
#include "content/public/common/content_switches.h"
#include "content/public/common/result_codes.h"

#include "shell/browser/browser.h"
#include "shell/browser/feature_list.h"
#include "shell/browser/javascript_environment.h"
#include "shell/browser/ui/cocoa/views_delegate_mac.h"
#include "shell/common/node_bindings.h"
#include "shell/common/node_includes.h"
#include "shell/views/shell.h"
#include "shell/views/shell_platform_delegate.h"
#include "shell/views/shell_browser_context.h"

// #include "shell/browser/browser.h"

namespace electron {
  namespace {
    // GURL GetStartupURL() {
    //   return GURL("https://www.baidu.com");
    // }
  }

  // static
  ElectronBrowserMainParts* ElectronBrowserMainParts::self_ = nullptr;

  ElectronBrowserMainParts::ElectronBrowserMainParts(
      const content::MainFunctionParams& params):
      node_bindings_(
          NodeBindings::Create(NodeBindings::BrowserEnvironment::kBrowser)), 
          browser_(std::make_unique<Browser>()) {
    // DCHECK(!self_) << "Cannot have two ElectronBrowserMainParts";
    self_ = this;
  }

  ElectronBrowserMainParts::~ElectronBrowserMainParts() = default;

    // static
  ElectronBrowserMainParts* ElectronBrowserMainParts::Get() {
    // DCHECK(self_);
    return self_;
  }

  int ElectronBrowserMainParts::PreEarlyInitialization() {
    field_trial_list_ = std::make_unique<base::FieldTrialList>(nullptr);

    return GetExitCode();
  }

  void ElectronBrowserMainParts::PostEarlyInitialization() {
    js_env_ = std::make_unique<JavascriptEnvironment>(node_bindings_->uv_loop());

    v8::HandleScope scope(js_env_->isolate());

    node_bindings_->Initialize();

    node::Environment* env = node_bindings_->CreateEnvironment(
        js_env_->context(), js_env_->platform());

    node_env_ = std::make_unique<NodeEnvironment>(env);

    node_bindings_->LoadEnvironment(env);    

    InitializeFeatureList();

    // Initialize field trials.
    InitializeFieldTrials();
  }

  void ElectronBrowserMainParts::ToolkitInitialized() {
    views_delegate_ = std::make_unique<ViewsDelegateMac>();
  }

  int ElectronBrowserMainParts::GetExitCode() const {
    return exit_code_.value_or(content::RESULT_CODE_NORMAL_EXIT);
  }

  void ElectronBrowserMainParts::PreCreateMainMessageLoopCommon() {
  #if defined(OS_MAC)
    InitializeMainNib();
    RegisterURLHandler();
  #endif
  }

  int ElectronBrowserMainParts::PreMainMessageLoopRun() {
    // 这个东西好像是根据url控制webUI的
    // content::WebUIControllerFactory::RegisterFactory(ElectronWebUIControllerFactory::GetInstance());

    // Notify observers that main thread message loop was initialized.
    // Browser::Get() = ElectronBrowserMainParts实例
    // Browser::Get()->PreMainMessageLoopRun();

    // Shell::Initialize(std::make_unique<ShellPlatformDelegate>());

    // set_browser_context(new ShellBrowserContext(false));

    // Shell::CreateNewWindow(browser_context_.get(), GetStartupURL(), nullptr);

    return 0;
  }
  
} // namespace electron


