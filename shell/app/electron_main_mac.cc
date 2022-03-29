// #include "shell/app/electron_library_main.h"
//#include "content/public/app/content_main.h"
//#include "content/public/app/content_main_delegate.h"
#include <cstdlib>
#include <memory>

#include "electron/buildflags/buildflags.h"
#include "electron/fuses.h"
#include "shell/app/electron_library_main.h"
#include "shell/common/electron_constants.h"

#if defined(HELPER_EXECUTABLE) && !defined(MAS_BUILD)
#include <mach-o/dyld.h>
#include <cstdio>

#include "sandbox/mac/seatbelt_exec.h"  // nogncheck
#endif

int main(int argc, char* argv[]) {
#if defined(HELPER_EXECUTABLE) && !defined(MAS_BUILD)    
  uint32_t exec_path_size = 0;
  int rv = _NSGetExecutablePath(NULL, &exec_path_size);
  if (rv != -1) {
    fprintf(stderr, "_NSGetExecutablePath: get length failed\n");
    abort();
  }

  auto exec_path = std::make_unique<char[]>(exec_path_size);

  rv = _NSGetExecutablePath(exec_path.get(), &exec_path_size);
  if (rv != 0) {
    fprintf(stderr, "_NSGetExecutablePath: get path failed\n");
    abort();
  }

  // gpu的启动还和这个东西有关系的？？？
  sandbox::SeatbeltExecServer::CreateFromArgumentsResult seatbelt =
      sandbox::SeatbeltExecServer::CreateFromArguments(exec_path.get(), argc,
                                                       argv);
                                                       
  if (seatbelt.sandbox_required) {
    if (!seatbelt.server) {
      fprintf(stderr, "Failed to create seatbelt sandbox server.\n");
      abort();
    }
    if (!seatbelt.server->InitializeSandbox()) {
      fprintf(stderr, "Failed to initialize sandbox.\n");
      abort();
    }
  }
#endif  // defined(HELPER_EXECUTABLE) && !defined(MAS_BUILD)  

  return ElectronMain(argc, argv);
}