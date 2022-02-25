#ifndef ELECTRON_SHELL_APP_ELECTRON_CONTENT_CLIENT_H_
#define ELECTRON_SHELL_APP_ELECTRON_CONTENT_CLIENT_H_

#include <vector>

#include "content/public/common/content_client.h"

namespace electron {
class ElectronContentClient : public content::ContentClient {};
}  // namespace electron

#endif