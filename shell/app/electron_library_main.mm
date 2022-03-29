//
// Created by 余圣源 on 2022/2/11.
//
#include <utility>

#include "shell/app/electron_library_main.h"

#include "base/at_exit.h"
#include "content/public/app/content_main.h"
#include "electron/fuses.h"
#include "shell/app/electron_main_delegate.h"
#include "shell/common/electron_command_line.h"
#include "shell/common/mac/main_application_bundle.h"

using namespace electron;

int ElectronMain(int argc, char* argv[]) {	
	electron::ElectronMainDelegate delegate;
	content::ContentMainParams params(&delegate);
	params.argc = argc;
	params.argv = const_cast<const char**>(argv);
	electron::ElectronCommandLine::Init(argc, argv);

	return content::ContentMain(std::move(params));
}