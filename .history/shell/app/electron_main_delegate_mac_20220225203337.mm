#include "shell/app/electron_main_delegate.h"

#include <string>

#include "base/files/file_path.h"
#include "base/files/file_util.h"
#include "base/mac/bundle_locations.h"
#include "base/mac/foundation_util.h"
#include "base/mac/scoped_nsautorelease_pool.h"
#include "base/path_service.h"
#include "base/strings/sys_string_conversions.h"
#include "content/common/mac_helpers.h"
#include "content/public/common/content_paths.h"
#include "ppapi/buildflags/buildflags.h"
#include "shell/browser/mac/electron_application.h"
#include "shell/common/application_info.h"
#include "shell/common/mac/main_application_bundle.h"

namespace electron {
	namespace {
		base::FilePath GetFrameworksPath() {
			return MainApplicationBundlePath().Append("Contents").Append("Frameworks");
		}
		
		base::FilePath GetHelperAppPath(const base::FilePath& frameworks_path,
																		const std::string& name) {
			// Figure out what helper we are running
			base::FilePath path;
			base::PathService::Get(base::FILE_EXE, &path);

			std::string helper_name = "Helper";

			if (base::EndsWith(path.value(), content::kMacHelperSuffix_renderer,
												 base::CompareCase::SENSITIVE)) {
				helper_name += content::kMacHelperSuffix_renderer;
			} else if (base::EndsWith(path.value(), content::kMacHelperSuffix_gpu,
																base::CompareCase::SENSITIVE)) {
				helper_name += content::kMacHelperSuffix_gpu;
#if BUILDFLAG(ENABLE_PLUGINS)
			} else if (base::EndsWith(path.value(), content::kMacHelperSuffix_plugin,
																base::CompareCase::SENSITIVE)) {
				helper_name += content::kMacHelperSuffix_plugin;
#endif
			}

			return frameworks_path.Append(name + " " + helper_name + ".app")
      .Append("Contents")
      .Append("MacOS")
      .Append(name + " " + helper_name);
		}
	}

	void ElectronMainDelegate::OverrideFrameworkBundlePath() {
		base::mac::SetOverrideFrameworkBundlePath(
				GetFrameworksPath().Append(ELECTRON_PRODUCT_NAME " Framework.framework"));
	}
	
	// 这个东西也是和register的那个provider相关的
	void ElectronMainDelegate::OverrideChildProcessPath() {
		base::FilePath frameworks_path = GetFrameworksPath();
		base::FilePath helper_path =
						GetHelperAppPath(frameworks_path, ELECTRON_PRODUCT_NAME);
		printf("haha1: %s", helper_path.value.c_str());				
		if (!base::PathExists(helper_path))
			helper_path = GetHelperAppPath(frameworks_path, GetApplicationName());
		printf("haha2: %s", helper_path.value.c_str());		
		if (!base::PathExists(helper_path))
			LOG(FATAL) << "Unable to find helper app";
		base::PathService::Override(content::CHILD_PROCESS_EXE, helper_path);
	}
	// 这个函数不知道是找一个什么bundle，然后设置这bundle的id
	void ElectronMainDelegate::SetUpBundleOverrides() {
		base::mac::ScopedNSAutoreleasePool pool;
		NSBundle* bundle = MainApplicationBundle();
		std::string base_bundle_id =
						base::SysNSStringToUTF8([bundle bundleIdentifier]);
		// 这句话看样子像是设置那个mac开始启动项目的信息
		NSString* team_id = [bundle objectForInfoDictionaryKey:@"ElectronTeamID"];
		if (team_id)
			base_bundle_id = base::SysNSStringToUTF8(team_id) + "." + base_bundle_id;
		base::mac::SetBaseBundleID(base_bundle_id.c_str());
	}
	
	void RegisterAtomCrApp() {
		// Force the NSApplication subclass to be used.
		[AtomApplication sharedApplication];
	}
}