// Copyright (c) 2013 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef ELECTRON_SHELL_BROWSER_ELECTRON_BROWSER_MAIN_PARTS_H_
#define ELECTRON_SHELL_BROWSER_ELECTRON_BROWSER_MAIN_PARTS_H_

#include <memory>
#include <string>

#include "base/callback.h"
#include "base/timer/timer.h"
#include "content/public/browser/browser_main_parts.h"
#include "content/public/common/main_function_params.h"
#include "shell/views/shell_browser_context.h"
#include "third_party/abseil-cpp/absl/types/optional.h"

class BrowserProcessImpl;

namespace base {
class FieldTrialList;
}

namespace electron {
  class ShellBrowserContext;
  class NodeBindings;

  // class Browser;

  class ElectronBrowserMainParts : public content::BrowserMainParts {
  public:
    explicit ElectronBrowserMainParts(const content::MainFunctionParams& params);
    ~ElectronBrowserMainParts() override;

    // disable copy
    ElectronBrowserMainParts(const ElectronBrowserMainParts&) = delete;
    ElectronBrowserMainParts& operator=(const ElectronBrowserMainParts&) = delete;

    static ElectronBrowserMainParts* Get();

    // Gets the exit code
    int GetExitCode() const;

    // Browser* browser() { return browser_.get(); }

  protected:
    // content::BrowserMainParts:
    int PreEarlyInitialization() override;
    void PostEarlyInitialization() override;
    // int PreCreateThreads() override;
    // void ToolkitInitialized() override;
    int PreMainMessageLoopRun() override;
    // void WillRunMainMessageLoop(
    //     std::unique_ptr<base::RunLoop>& run_loop) override;
    // void PostCreateMainMessageLoop() override;
    // void PostMainMessageLoopRun() override;
    void PreCreateMainMessageLoop() override;
    // void PostCreateThreads() override;
    // void PostDestroyThreads() override;

    void set_browser_context(ShellBrowserContext* context) {
      browser_context_.reset(context);
    }

  private:
    void PreCreateMainMessageLoopCommon();

    std::unique_ptr<NodeBindings> node_bindings_;

    std::unique_ptr<ShellBrowserContext> browser_context_;

  #if defined(OS_MAC)
    void FreeAppDelegate();
    void RegisterURLHandler();
    void InitializeMainNib();
  #endif

    // std::unique_ptr<Browser> browser_;

    // A place to remember the exit code once the message loop is ready.
    // Before then, we just exit() without any intermediate steps.
    absl::optional<int> exit_code_;

    static ElectronBrowserMainParts* self_;

    std::unique_ptr<base::FieldTrialList> field_trial_list_;
  };

}  // namespace electron

#endif  // ELECTRON_SHELL_BROWSER_ELECTRON_BROWSER_MAIN_PARTS_H_
