// Copyright (c) 2013 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef ELECTRON_SHELL_APP_ELECTRON_MAIN_DELEGATE_H_
#define ELECTRON_SHELL_APP_ELECTRON_MAIN_DELEGATE_H_

#include <memory>
#include <string>

#include "content/public/app/content_main_delegate.h"
#include "content/public/common/content_client.h"
// todo 有一个奇怪的问题这个几个头文件如果不定义的话下面的智能指针就会报错，但是源码里面确实没有他们呀？？
#include "content/public/browser/content_browser_client.h"
#include "content/public/gpu/content_gpu_client.h"
#include "content/public/renderer/content_renderer_client.h"
#include "content/public/utility/content_utility_client.h"


namespace tracing {
class TracingSamplerProfiler;
}

namespace electron {

std::string LoadResourceBundle(const std::string& locale);

class ElectronMainDelegate : public content::ContentMainDelegate {
 public:
  static const char* const kNonWildcardDomainNonPortSchemes[];
  static const size_t kNonWildcardDomainNonPortSchemesSize;
  ElectronMainDelegate();
  ~ElectronMainDelegate() override;

  // disable copy
  ElectronMainDelegate(const ElectronMainDelegate&) = delete;
  ElectronMainDelegate& operator=(const ElectronMainDelegate&) = delete;

 protected:
  // content::ContentMainDelegate:
  bool BasicStartupComplete(int* exit_code) override;
  void PreSandboxStartup() override;
  void SandboxInitialized(const std::string& process_type) override;
  void PreBrowserMain() override;
  content::ContentBrowserClient* CreateContentBrowserClient() override;
  content::ContentGpuClient* CreateContentGpuClient() override;
  content::ContentRendererClient* CreateContentRendererClient() override;
  content::ContentUtilityClient* CreateContentUtilityClient() override;
  absl::variant<int, content::MainFunctionParams> RunProcess(
      const std::string& process_type,
      content::MainFunctionParams main_function_params) override;
  bool ShouldCreateFeatureList() override;
  bool ShouldLockSchemeRegistry() override;
#if defined(OS_LINUX)
  void ZygoteForked() override;
#endif

 private:
#if defined(OS_MAC)
  void OverrideChildProcessPath();
  void OverrideFrameworkBundlePath();
  void SetUpBundleOverrides();
#endif

  std::unique_ptr<content::ContentBrowserClient> browser_client_;
  std::unique_ptr<content::ContentClient> content_client_;
  std::unique_ptr<content::ContentGpuClient> gpu_client_;
  std::unique_ptr<content::ContentRendererClient> renderer_client_;
  std::unique_ptr<content::ContentUtilityClient> utility_client_;
  std::unique_ptr<tracing::TracingSamplerProfiler> tracing_sampler_profiler_;
};

}  // namespace electron

#endif  // ELECTRON_SHELL_APP_ELECTRON_MAIN_DELEGATE_H_
