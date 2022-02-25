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

// #include "shell/browser/browser.h"

namespace electron {
  namespace {}

  // static
  ElectronBrowserMainParts* ElectronBrowserMainParts::self_ = nullptr;

  ElectronBrowserMainParts::ElectronBrowserMainParts(
      const content::MainFunctionParams& params) {
      // : browser_(std::make_unique<Browser>()) {
    // DCHECK(!self_) << "Cannot have two ElectronBrowserMainParts";
    self_ = this;
  }

  ElectronBrowserMainParts::~ElectronBrowserMainParts() = default;

    // static
  ElectronBrowserMainParts* ElectronBrowserMainParts::Get() {
    // DCHECK(self_);
    return self_;
  }

  // int ElectronBrowserMainParts::PreMainMessageLoopRun() {
  //   // 这个东西好像是根据url控制webUI的
  //   content::WebUIControllerFactory::RegisterFactory(ElectronWebUIControllerFactory::GetInstance());

  //   // Notify observers that main thread message loop was initialized.
  //   // Browser::Get() = ElectronBrowserMainParts实例
  //   Browser::Get()->PreMainMessageLoopRun();
  // }
  
} // namespace electron


