#include "shell/browser/electron_browser_context.h"

#include <memory>
#include <utility>

#include "content/public/browser/browser_context.h"
#include "content/public/browser/resource_context.h"
#include "content/public/browser/download_manager_delegate.h"
#include "content/public/browser/permission_controller_delegate.h"
#include "content/public/browser/background_sync_controller.h"
#include "content/public/browser/content_index_provider.h"
#include "content/public/browser/client_hints_controller_delegate.h"
#include "shell/browser/electron_download_manager_delegate.h"

namespace electron {
  ElectronBrowserContext::ElectronResourceContext::ElectronResourceContext() {}

  ElectronBrowserContext::ElectronResourceContext::~ElectronResourceContext() {
  }

  ElectronBrowserContext::ElectronBrowserContext(bool off_the_record)
    : resource_context_(std::make_unique<ElectronResourceContext>()),
      off_the_record_(off_the_record) {
   
  }

  ElectronBrowserContext::~ElectronBrowserContext() {

  }

  std::unique_ptr<content::ZoomLevelDelegate> ElectronBrowserContext::CreateZoomLevelDelegate(
      const base::FilePath&) {
    return nullptr;
  }

  base::FilePath ElectronBrowserContext::GetPath() {
    return path_;
  }

  bool ElectronBrowserContext::IsOffTheRecord() {
    return off_the_record_;
  }

  content::DownloadManagerDelegate* ElectronBrowserContext::GetDownloadManagerDelegate()  {
    if (!download_manager_delegate_.get()) {
      download_manager_delegate_ =
          std::make_unique<ElectronDownloadManagerDelegate>();
      download_manager_delegate_->SetDownloadManager(GetDownloadManager());
    }

    return download_manager_delegate_.get();
  }

  content::ResourceContext* ElectronBrowserContext::GetResourceContext()  {
    return resource_context_.get();
  }

  content::BrowserPluginGuestManager* ElectronBrowserContext::GetGuestManager() {
    return nullptr;
  }

  storage::SpecialStoragePolicy* ElectronBrowserContext::GetSpecialStoragePolicy() {
    return nullptr;
  }

  content::PlatformNotificationService*
  ElectronBrowserContext::GetPlatformNotificationService() {
    return nullptr;
  }

  content::PushMessagingService* ElectronBrowserContext::GetPushMessagingService() {
    return nullptr;
  }

  content::StorageNotificationService*
  ElectronBrowserContext::GetStorageNotificationService() {
    return nullptr;
  }

  content::SSLHostStateDelegate* ElectronBrowserContext::GetSSLHostStateDelegate() {
    return nullptr;
  }

  content::PermissionControllerDelegate*
  ElectronBrowserContext::GetPermissionControllerDelegate() {
    // if (!permission_manager_.get())
    //   permission_manager_ = std::make_unique<ElectronPermissionManager>();
    return permission_manager_.get();
  }

  content::ClientHintsControllerDelegate*
  ElectronBrowserContext::GetClientHintsControllerDelegate() {
    return client_hints_controller_delegate_;
  }

  content::BackgroundFetchDelegate* ElectronBrowserContext::GetBackgroundFetchDelegate() {
    return nullptr;
  }

  content::BackgroundSyncController* ElectronBrowserContext::GetBackgroundSyncController() {
    // if (!background_sync_controller_) {
    //   background_sync_controller_ =
    //       std::make_unique<MockBackgroundSyncController>();
    // }
    return background_sync_controller_.get();
  }

  content::BrowsingDataRemoverDelegate*
  ElectronBrowserContext::GetBrowsingDataRemoverDelegate() {
    return nullptr;
  }

  content::ContentIndexProvider* ElectronBrowserContext::GetContentIndexProvider() {
    // if (!content_index_provider_)
    //   content_index_provider_ = std::make_unique<ElectronContentIndexProvider>();
    return content_index_provider_.get();
  }

}