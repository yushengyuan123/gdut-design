// Copyright (c) 2013 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "shell/common/node_bindings_mac.h"

#include <errno.h>
#include <sys/select.h>
#include <sys/sysctl.h>
#include <sys/time.h>
#include <sys/types.h>

#include "shell/common/node_includes.h"

namespace electron {

NodeBindingsMac::NodeBindingsMac(BrowserEnvironment browser_env)
    : NodeBindings(browser_env) {}

NodeBindingsMac::~NodeBindingsMac() = default;

// static
NodeBindings* NodeBindings::Create(BrowserEnvironment browser_env) {
  return new NodeBindingsMac(browser_env);
}

}  // namespace electron
