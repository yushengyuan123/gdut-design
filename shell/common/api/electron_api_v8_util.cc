// Copyright (c) 2013 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include <utility>

#include "base/hash/hash.h"
#include "electron/buildflags/buildflags.h"
// #include "shell/common/api/electron_api_key_weak_map.h"
// #include "shell/common/gin_converters/content_converter.h"
// #include "shell/common/gin_converters/gurl_converter.h"
#include "shell/common/gin_converters/std_converter.h"
#include "shell/common/gin_helper/dictionary.h"
#include "shell/common/node_includes.h"
#include "url/origin.h"
#include "v8/include/v8-profiler.h"

namespace std {

// The hash function used by DoubleIDWeakMap.
template <typename Type1, typename Type2>
struct hash<std::pair<Type1, Type2>> {
  std::size_t operator()(std::pair<Type1, Type2> value) const {
    return base::HashInts(base::Hash(value.first), value.second);
  }
};

}  // namespace std

namespace gin {

template <typename Type1, typename Type2>
struct Converter<std::pair<Type1, Type2>> {
  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     std::pair<Type1, Type2>* out) {
    if (!val->IsArray())
      return false;

    v8::Local<v8::Array> array = val.As<v8::Array>();
    if (array->Length() != 2)
      return false;

    auto context = isolate->GetCurrentContext();
    return Converter<Type1>::FromV8(
               isolate, array->Get(context, 0).ToLocalChecked(), &out->first) &&
           Converter<Type2>::FromV8(
               isolate, array->Get(context, 1).ToLocalChecked(), &out->second);
  }
};

}  // namespace gin

namespace {

v8::Local<v8::Value> GetHiddenValue(v8::Isolate* isolate,
                                    v8::Local<v8::Object> object,
                                    v8::Local<v8::String> key) {
  v8::Local<v8::Context> context = isolate->GetCurrentContext();
  v8::Local<v8::Private> privateKey = v8::Private::ForApi(isolate, key);
  v8::Local<v8::Value> value;
  v8::Maybe<bool> result = object->HasPrivate(context, privateKey);
  if (!(result.IsJust() && result.FromJust()))
    return v8::Local<v8::Value>();
  if (object->GetPrivate(context, privateKey).ToLocal(&value))
    return value;
  return v8::Local<v8::Value>();
}

void Initialize(v8::Local<v8::Object> exports,
                v8::Local<v8::Value> unused,
                v8::Local<v8::Context> context,
                void* priv) {
  gin_helper::Dictionary dict(context->GetIsolate(), exports);
  dict.SetMethod("getHiddenValue", &GetHiddenValue);
}

}  // namespace

NODE_LINKED_MODULE_CONTEXT_AWARE(electron_common_v8_util, Initialize)
