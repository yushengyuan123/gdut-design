#include "shell/browser/api/electron_api_session.h"

#include <algorithm>
#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "gin/arguments.h"
#include "gin/handle.h"
#include "shell/browser/electron_browser_context.h"

namespace electron {
namespace api {

gin::WrapperInfo Session::kWrapperInfo = {gin::kEmbedderNativeGin};  

Session::Session(v8::Isolate* isolate, ElectronBrowserContext* browser_context)
      :browser_context_(browser_context) {
}

Session::~Session() {

}


// static
gin::Handle<Session> Session::FromPartition(v8::Isolate* isolate,
                                            const std::string& partition,
                                            base::DictionaryValue options) {
  ElectronBrowserContext* browser_context = new ElectronBrowserContext(false);

  // if (partition.empty()) {
  //   browser_context =
  //       ElectronBrowserContext::From("", false, std::move(options));
  // } else if (base::StartsWith(partition, kPersistPrefix,
  //                             base::CompareCase::SENSITIVE)) {
  //   std::string name = partition.substr(8);
  //   browser_context =
  //       ElectronBrowserContext::From(name, false, std::move(options));
  // } else {
  //   browser_context =
  //       ElectronBrowserContext::From(partition, true, std::move(options));
  // }

  return CreateFrom(isolate, browser_context);
}

// static
gin::Handle<Session> Session::CreateFrom(
    v8::Isolate* isolate,
    ElectronBrowserContext* browser_context) {
  // Session* existing = FromBrowserContext(browser_context);
  // if (existing)
  //   return gin::CreateHandle(isolate, existing);

  auto handle =
      gin::CreateHandle(isolate, new Session(isolate, browser_context));

  // The Sessions should never be garbage collected, since the common pattern is
  // to use partition strings, instead of using the Session object directly.
  // handle->Pin(isolate);


  return handle;
}

}  // namespace api
}  // namespace electron

