// Copyright (c) 2019 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "shell/browser/electron_gpu_client.h"

#include "base/environment.h"

#if defined(OS_WIN)
#include <windows.h>
#endif

namespace electron {

ElectronGpuClient::ElectronGpuClient() = default;


}  // namespace electron
