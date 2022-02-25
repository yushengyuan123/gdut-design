#include "shell/utility/electron_content_utility_client.h"

namespace electron {
  namespace {}


ElectronContentUtilityClient::ElectronContentUtilityClient() {
#if BUILDFLAG(ENABLE_PRINT_PREVIEW) && defined(OS_WIN)
  printing_handler_ = std::make_unique<printing::PrintingHandler>();
#endif
}

ElectronContentUtilityClient::~ElectronContentUtilityClient() = default;
}