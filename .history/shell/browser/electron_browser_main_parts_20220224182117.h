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

class BrowserProcessImpl;

namespace electron {

  

class ElectronBrowserMainParts : public content::BrowserMainParts {
 public:
  explicit ElectronBrowserMainParts(const content::MainFunctionParams& params);
  ~ElectronBrowserMainParts() override;

  // disable copy
  ElectronBrowserMainParts(const ElectronBrowserMainParts&) = delete;
  ElectronBrowserMainParts& operator=(const ElectronBrowserMainParts&) = delete;

  static ElectronBrowserMainParts* Get();

 protected:
  // content::BrowserMainParts:
  // int PreCreateThreads() override;
  // void ToolkitInitialized() override;
  int PreMainMessageLoopRun() override;
  void WillRunMainMessageLoop(
      std::unique_ptr<base::RunLoop>& run_loop) override;
  void PostCreateMainMessageLoop() override;
  void PostMainMessageLoopRun() override;
  void PreCreateMainMessageLoop() override;
  void PostCreateThreads() override;
  void PostDestroyThreads() override;

 private:
  void PreCreateMainMessageLoopCommon();

  // A fake BrowserProcess object that used to feed the source code from chrome.
  std::unique_ptr<BrowserProcessImpl> fake_browser_process_;

  std::unique_ptr<Browser> browser_;

  static ElectronBrowserMainParts* self_;
};

}  // namespace electron

#endif  // ELECTRON_SHELL_BROWSER_ELECTRON_BROWSER_MAIN_PARTS_H_