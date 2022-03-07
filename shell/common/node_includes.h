// Copyright (c) 2013 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef ELECTRON_SHELL_COMMON_NODE_INCLUDES_H_
#define ELECTRON_SHELL_COMMON_NODE_INCLUDES_H_

// Include common headers for using node APIs.

#ifdef NODE_SHARED_MODE
#define BUILDING_NODE_EXTENSION
#endif

#undef debug_string    // This is defined in macOS SDK in AssertMacros.h.
#undef require_string  // This is defined in macOS SDK in AssertMacros.h.
// 这个头文件比较关键没有了他，所以node的内部方法引用都是错误的，具体为什么还没有研究
#include "electron/push_and_undef_node_defines.h"

#include "env-inl.h"
#include "env.h"
#include "node.h"
#include "node_buffer.h"
#include "node_errors.h"
#include "node_internals.h"
#include "node_native_module_env.h"
#include "node_options-inl.h"
#include "node_options.h"
#include "node_platform.h"
#include "tracing/agent.h"

#include "electron/pop_node_defines.h"

// Alternative to NODE_MODULE_CONTEXT_AWARE_X.
// Allows to explicitly register builtin modules instead of using
// __attribute__((constructor)).
#define NODE_LINKED_MODULE_CONTEXT_AWARE(modname, regfunc) \
  NODE_MODULE_CONTEXT_AWARE_CPP(modname, regfunc, nullptr, NM_F_LINKED)

#endif  // ELECTRON_SHELL_COMMON_NODE_INCLUDES_H_
