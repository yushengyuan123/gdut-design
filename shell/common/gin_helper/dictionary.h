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

  // Differences from the Get method in gin::Dictionary:
  // 1. This is a const method;
  // 2. It checks whether the key exists before reading;
  // 3. It accepts arbitrary type of key.
  template <typename K, typename V>
  bool Get(const K& key, V* out) const {
    // Check for existence before getting, otherwise this method will always
    // returns true when T == v8::Local<v8::Value>.
    v8::Local<v8::Context> context = isolate()->GetCurrentContext();
    v8::Local<v8::Value> v8_key = gin::ConvertToV8(isolate(), key);
    v8::Local<v8::Value> value;
    v8::Maybe<bool> result = GetHandle()->Has(context, v8_key);
    if (result.IsJust() && result.FromJust() &&
        GetHandle()->Get(context, v8_key).ToLocal(&value))
      return gin::ConvertFromV8(isolate(), value, out);
    return false;
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

  // Like normal Get but put result in an absl::optional.
  template <typename T>
  bool GetOptional(base::StringPiece key, absl::optional<T>* out) const {
    T ret;
    if (Get(key, &ret)) {
      out->emplace(std::move(ret));
      return true;
    } else {
      return false;
    }
  }

  template <typename T>
  bool GetHidden(base::StringPiece key, T* out) const {
    v8::Local<v8::Context> context = isolate()->GetCurrentContext();
    v8::Local<v8::Private> privateKey =
        v8::Private::ForApi(isolate(), gin::StringToV8(isolate(), key));
    v8::Local<v8::Value> value;
    v8::Maybe<bool> result = GetHandle()->HasPrivate(context, privateKey);
    if (result.IsJust() && result.FromJust() &&
        GetHandle()->GetPrivate(context, privateKey).ToLocal(&value))
      return gin::ConvertFromV8(isolate(), value, out);
    return false;
  }

  template <typename T>
  bool SetHidden(base::StringPiece key, T val) {
    v8::Local<v8::Value> v8_value;
    if (!gin::TryConvertToV8(isolate(), val, &v8_value))
      return false;
    v8::Local<v8::Context> context = isolate()->GetCurrentContext();
    v8::Local<v8::Private> privateKey =
        v8::Private::ForApi(isolate(), gin::StringToV8(isolate(), key));
    v8::Maybe<bool> result =
        GetHandle()->SetPrivate(context, privateKey, v8_value);
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