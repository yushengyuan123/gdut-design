//
// Created by 余圣源 on 2022/2/11.
//

#ifndef DADA_ELECTRON_MAIN_DELEGATE_H
#define DADA_ELECTRON_MAIN_DELEGATE_H

#include <memory>
#include <string>

#include "content/public/app/content_main_delegate.h"
#include "content/public/common/content_client.h"
#include "string"

namespace tracing {
	class TracingSamplerProfiler;
}

namespace electron {

std::string LoadResourceBundle(const std::string& locale);

class ElectronMainDelegate : public content::ContentMainDelegate {
	public:
		static const char *const kNonWildcardDomainNonPortSchemes[];
		static const size_t kNonWildcardDomainNonPortSchemesSize;
		ElectronMainDelegate();
		~ElectronMainDelegate() override;
		
		ElectronMainDelegate(const ElectronMainDelegate&) = delete;
		ElectronMainDelegate& operator=(const ElectronMainDelegate&) = delete;


	protected:
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

	private:
		void OverrideChildProcessPath();
		void OverrideFrameworkBundlePath();
		void SetUpBundleOverrides();
		
		
		std::unique_ptr<content::ContentBrowserClient> browser_client_;
		std::unique_ptr<content::ContentClient> content_client_;
		std::unique_ptr<content::ContentGpuClient> gpu_client_;
		std::unique_ptr<content::ContentRendererClient> renderer_client_;
		std::unique_ptr<content::ContentUtilityClient> utility_client_;
		std::unique_ptr<tracing::TracingSamplerProfiler> tracing_sampler_profiler_;
};
}

#endif //DADA_ELECTRON_MAIN_DELEGATE_H
