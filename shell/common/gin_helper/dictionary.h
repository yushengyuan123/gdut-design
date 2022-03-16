#ifndef ELECTRON_SHELL_COMMON_GIN_HELPER_DICTIONARY_H_
#define ELECTRON_SHELL_COMMON_GIN_HELPER_DICTIONARY_H_

#include <type_traits>
#include <utility>

#include "gin/dictionary.h"
#include "shell/common/gin_converters/std_converter.h"
#include "shell/common/gin_helper/accessor.h"
#include "shell/common/gin_helper/function_template.h"
#include "third_party/abseil-cpp/absl/types/optional.h"

namespace gin_helper {
class Dictionary : public gin::Dictionary {
 public:
  Dictionary() : gin::Dictionary(nullptr) {}

  Dictionary(v8::Isolate* isolate, v8::Local<v8::Object> object)
      : gin::Dictionary(isolate, object) {}

  Dictionary(const gin::Dictionary& dict)  // NOLINT(runtime/explicit)
      : gin::Dictionary(dict) {}

  template <typename T>
  bool SetMethod(base::StringPiece key, const T& callback) {
    auto context = isolate()->GetCurrentContext();
    auto templ = CallbackTraits<T>::CreateTemplate(isolate(), callback);
    return GetHandle()
        ->Set(context, gin::StringToV8(isolate(), key),
              templ->GetFunction(context).ToLocalChecked())
        .ToChecked();
  }

    // Differences from the Set method in gin::Dictionary:
  // 1. It accepts arbitrary type of key.
  template <typename K, typename V>
  bool Set(const K& key, const V& val) {
    v8::Local<v8::Value> v8_value;
    if (!gin::TryConvertToV8(isolate(), val, &v8_value))
      return false;
    v8::Maybe<bool> result =
        GetHandle()->Set(isolate()->GetCurrentContext(),
                         gin::ConvertToV8(isolate(), key), v8_value);
    return !result.IsNothing() && result.FromJust();
  }

  v8::Local<v8::Object> GetHandle() const {
    return gin::ConvertToV8(isolate(),
                            *static_cast<const gin::Dictionary*>(this))
        .As<v8::Object>();
  }
};
}  // namespace gin_helper

namespace gin {

template <>
struct Converter<gin_helper::Dictionary> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   gin_helper::Dictionary val) {
    return val.GetHandle();
  }
  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     gin_helper::Dictionary* out) {
    gin::Dictionary gdict(isolate);
    if (!ConvertFromV8(isolate, val, &gdict))
      return false;
    *out = gin_helper::Dictionary(gdict);
    return true;
  }
};
}  // namespace gin

#endif