// Copyright (c) 2013 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef ELECTRON_SHELL_COMMON_NODE_BINDINGS_H_
#define ELECTRON_SHELL_COMMON_NODE_BINDINGS_H_

#include "base/files/file_path.h"
#include "base/memory/weak_ptr.h"
#include "uv.h"  // NOLINT(build/include_directory)
#include "v8/include/v8.h"

namespace node {
class Environment;
class MultiIsolatePlatform;
class IsolateData;
}  // namespace node

namespace electron {
  class NodeBindings {
    public:
      enum class BrowserEnvironment { kBrowser, kRenderer, kWorker };

      // disable copy
      NodeBindings(const NodeBindings&) = delete;
      NodeBindings& operator=(const NodeBindings&) = delete;

      // Create the environment and load node.js.
      // node::Environment* CreateEnvironment(v8::Handle<v8::Context> context,
      //                                     node::MultiIsolatePlatform* platform);

      // Load node.js in the environment.
      void LoadEnvironment();                                    

      // Setup V8, libuv.
      void Initialize();

      uv_loop_t* uv_loop() const { return uv_loop_; }

    protected:
      explicit NodeBindings(BrowserEnvironment browser_env);

      const BrowserEnvironment browser_env_;

      uv_loop_t* uv_loop_;  
  };
}


#endif