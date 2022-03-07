#include "shell/views/shell_browser_context.h"

#include <memory>
#include <utility>

#include "content/public/browser/browser_context.h"
#include "content/public/browser/resource_context.h"
#include "content/public/browser/download_manager_delegate.h"
#include "content/public/browser/permission_controller_delegate.h"
#include "content/public/browser/background_sync_controller.h"
#include "content/public/browser/content_index_provider.h"
#include "content/public/browser/client_hints_controller_delegate.h"
#include "shell/views/shell_download_manager_delegate.h"

namespace electron {
  ShellBrowserContext::ShellResourceContext::ShellResourceContext() {}

  ShellBrowserContext::ShellResourceContext::~ShellResourceContext() {
  }

  ShellBrowserContext::ShellBrowserContext(bool off_the_record)
    : resource_context_(std::make_unique<ShellResourceContext>()),
      off_the_record_(off_the_record) {
   
  }

  ShellBrowserContext::~ShellBrowserContext() {

  }

  std::unique_ptr<content::ZoomLevelDelegate> ShellBrowserContext::CreateZoomLevelDelegate(
      const base::FilePath&) {
    return nullptr;
  }

  base::FilePath ShellBrowserContext::GetPath() {
    return path_;
  }

  bool ShellBrowserContext::IsOffTheRecord() {
    return off_the_record_;
  }

  content::DownloadManagerDelegate* ShellBrowserContext::GetDownloadManagerDelegate()  {
    if (!download_manager_delegate_.get()) {
      download_manager_delegate_ =
          std::make_unique<ShellDownloadManagerDelegate>();
      download_manager_delegate_->SetDownloadManager(GetDownloadManager());
    }

    return download_manager_delegate_.get();
  }

  content::ResourceContext* ShellBrowserContext::GetResourceContext()  {
    return resource_context_.get();
  }

  content::BrowserPluginGuestManager* ShellBrowserContext::GetGuestManager() {
    return nullptr;
  }

  storage::SpecialStoragePolicy* ShellBrowserContext::GetSpecialStoragePolicy() {
    return nullptr;
  }

  content::PlatformNotificationService*
  ShellBrowserContext::GetPlatformNotificationService() {
    return nullptr;
  }

  content::PushMessagingService* ShellBrowserContext::GetPushMessagingService() {
    return nullptr;
  }

  content::StorageNotificationService*
  ShellBrowserContext::GetStorageNotificationService() {
    return nullptr;
  }

  content::SSLHostStateDelegate* ShellBrowserContext::GetSSLHostStateDelegate() {
    return nullptr;
  }

  content::PermissionControllerDelegate*
  ShellBrowserContext::GetPermissionControllerDelegate() {
    // if (!permission_manager_.get())
    //   permission_manager_ = std::make_unique<ShellPermissionManager>();
    return permission_manager_.get();
  }

  content::ClientHintsControllerDelegate*
  ShellBrowserContext::GetClientHintsControllerDelegate() {
    return client_hints_controller_delegate_;
  }

  content::BackgroundFetchDelegate* ShellBrowserContext::GetBackgroundFetchDelegate() {
    return nullptr;
  }

  content::BackgroundSyncController* ShellBrowserContext::GetBackgroundSyncController() {
    // if (!background_sync_controller_) {
    //   background_sync_controller_ =
    //       std::make_unique<MockBackgroundSyncController>();
    // }
    return background_sync_controller_.get();
  }

  content::BrowsingDataRemoverDelegate*
  ShellBrowserContext::GetBrowsingDataRemoverDelegate() {
    return nullptr;
  }

  content::ContentIndexProvider* ShellBrowserContext::GetContentIndexProvider() {
    // if (!content_index_provider_)
    //   content_index_provider_ = std::make_unique<ShellContentIndexProvider>();
    return content_index_provider_.get();
  }

}