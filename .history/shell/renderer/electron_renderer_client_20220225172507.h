// Copyright (c) 2013 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef ELECTRON_SHELL_RENDERER_ELECTRON_RENDERER_CLIENT_H_
#define ELECTRON_SHELL_RENDERER_ELECTRON_RENDERER_CLIENT_H_

#include <memory>
#include <set>
#include <string>

#include "content/public/renderer/content_renderer_client.h"


namespace node {
class Environment;
}

namespace electron {

class ElectronBindings;
class NodeBindings;

class ElectronRendererClient : public content::ContentRendererClient {
 public:
  ElectronRendererClient();
  ~ElectronRendererClient() override;

  // disable copy
  ElectronRendererClient(const ElectronRendererClient&) = delete;
  ElectronRendererClient& operator=(const ElectronRendererClient&) = delete;
};

}  // namespace electron

#endif  // ELECTRON_SHELL_RENDERER_ELECTRON_RENDERER_CLIENT_H_
