// Copyright (c) 2015 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef ELECTRON_SHELL_UTILITY_ELECTRON_CONTENT_UTILITY_CLIENT_H_
#define ELECTRON_SHELL_UTILITY_ELECTRON_CONTENT_UTILITY_CLIENT_H_

#include <memory>

#include "content/public/utility/content_utility_client.h"


namespace electron {

class ElectronContentUtilityClient : public content::ContentUtilityClient {
 public:
  ElectronContentUtilityClient();
  ~ElectronContentUtilityClient() override;

  // disable copy
  ElectronContentUtilityClient(const ElectronContentUtilityClient&) = delete;
  ElectronContentUtilityClient& operator=(const ElectronContentUtilityClient&) =
      delete;

//   void ExposeInterfacesToBrowser(mojo::BinderMap* binders) override;
//   void RegisterMainThreadServices(mojo::ServiceFactory& services) override;
//   void RegisterIOThreadServices(mojo::ServiceFactory& services) override;

//  private:
// #if BUILDFLAG(ENABLE_PRINT_PREVIEW) && defined(OS_WIN)
//   std::unique_ptr<printing::PrintingHandler> printing_handler_;
// #endif

//   // True if the utility process runs with elevated privileges.
//   bool utility_process_running_elevated_ = false;
};

}  // namespace electron

#endif  // ELECTRON_SHELL_UTILITY_ELECTRON_CONTENT_UTILITY_CLIENT_H_
