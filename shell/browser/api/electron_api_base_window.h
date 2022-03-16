// Copyright (c) 2018 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef ELECTRON_SHELL_BROWSER_API_ELECTRON_API_BASE_WINDOW_H_
#define ELECTRON_SHELL_BROWSER_API_ELECTRON_API_BASE_WINDOW_H_

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "base/task/post_task.h"
#include "content/public/browser/browser_task_traits.h"
#include "content/public/browser/browser_thread.h"
#include "gin/handle.h"

#include "shell/common/gin_helper/arguments.h"
#include "shell/common/gin_helper/dictionary.h"

namespace electron {

namespace api {

class View;

class BaseWindow {
 public:


 protected:
  // Common constructor.
  BaseWindow(v8::Isolate* isolate, const gin_helper::Dictionary& options);

  // Creating independent BaseWindow instance.
  BaseWindow(gin_helper::Arguments* args,
             const gin_helper::Dictionary& options);

  ~BaseWindow();
};  // namespace electron
}  // namespace api
}  // namespace electron

#endif  // ELECTRON_SHELL_BROWSER_API_ELECTRON_API_BASE_WINDOW_H_
