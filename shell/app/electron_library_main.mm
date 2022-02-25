//
// Created by 余圣源 on 2022/2/11.
//
#include "content/public/app/content_main.h"
#include "shell/app/electron_library_main.h"
#include "shell/app/electron_main_delegate.h"
#include "shell/app/electron_main_delegate_mac.h"
#include "shell/common/electron_command_line.h"

using namespace electron;

int ElectronMain(int argc, char* argv[]) {	
	electron::ElectronMainDelegate delegate;
	content::ContentMainParams params(&delegate);
	params.argc = argc;
	params.argv = const_cast<const char**>(argv);

	return content::ContentMain(std::move(params));
}