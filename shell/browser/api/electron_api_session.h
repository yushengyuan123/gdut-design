#ifndef ELECTRON_SHELL_BROWSER_API_ELECTRON_API_SESSION_H_
#define ELECTRON_SHELL_BROWSER_API_ELECTRON_API_SESSION_H_

#include <string>
#include <vector>

#include "base/values.h"
#include "gin/handle.h"
#include "gin/wrappable.h"

#include "shell/common/gin_helper/wrappable.h"

namespace gin {
class Arguments;
}

namespace electron {
class ElectronBrowserContext;

namespace api {
class Session : public gin::Wrappable<Session> {
 public:
  static gin::Handle<Session> CreateFrom(
      v8::Isolate* isolate,
      ElectronBrowserContext* browser_context);

      static gin::WrapperInfo kWrapperInfo;

  // Gets the Session of |partition|.
  static gin::Handle<Session> FromPartition(
      v8::Isolate* isolate,
      const std::string& partition,
      base::DictionaryValue options = base::DictionaryValue());

  // disable copy
  Session(const Session&) = delete;
  Session& operator=(const Session&) = delete;

  ElectronBrowserContext* browser_context() const { return browser_context_; }

 protected:
  Session(v8::Isolate* isolate, ElectronBrowserContext* browser_context);
  ~Session() override;

 private:
//   v8::Isolate* isolate_;

  ElectronBrowserContext* browser_context_;
};
}  // namespace api

}  // namespace electron

#endif  // ELECTRON_SHELL_BROWSER_API_ELECTRON_API_SESSION_H_