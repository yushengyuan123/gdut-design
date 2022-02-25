// #include "shell/app/electron_library_main.h"
//#include "content/public/app/content_main.h"
//#include "content/public/app/content_main_delegate.h"
#include "shell/app/electron_library_main.h"

//class Person : public content::ContentMainDelegate {
//
//};
//
//int ElectronMain(int argc, char* argv[]) {
//  Person delegate;
//  content::ContentMainParams params(&delegate);
//  params.argc = argc;
//  params.argv = const_cast<const char**>(argv);
////   electron::ElectronCommandLine::Init(argc, argv);
//  return content::ContentMain(std::move(params));
//}

int main(int argc, char* argv[]) {
    return ElectronMain(argc, argv);
}