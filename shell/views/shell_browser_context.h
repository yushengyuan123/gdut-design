#ifndef CONTENT_SHELL_BROWSER_SHELL_BROWSER_CONTEXT_H_
#define CONTENT_SHELL_BROWSER_SHELL_BROWSER_CONTEXT_H_

#include <memory>

#include "base/files/file_path.h"
#include "base/memory/raw_ptr.h"
#include "base/memory/ref_counted.h"
#include "content/public/browser/browser_context.h"
#include "content/public/browser/resource_context.h"
#include "content/public/browser/download_manager_delegate.h"
#include "content/public/browser/permission_controller_delegate.h"
#include "content/public/browser/background_sync_controller.h"
#include "content/public/browser/content_index_provider.h"
#include "content/public/browser/client_hints_controller_delegate.h"

#include "shell/views/shell_download_manager_delegate.h"

namespace content {
  class BackgroundSyncController;
  class ContentIndexProvider;
  class ClientHintsControllerDelegate;
  class DownloadManagerDelegate;
  class PermissionControllerDelegate;
  class ZoomLevelDelegate;
}

namespace electron {
  class ShellDownloadManagerDelegate;

  class ShellBrowserContext : public content::BrowserContext {
    public:
      ShellBrowserContext(bool off_the_record);

      ShellBrowserContext(const ShellBrowserContext&) = delete;
      ShellBrowserContext& operator=(const ShellBrowserContext&) = delete;

      ~ShellBrowserContext() override;

      // BrowserContext implementation.
      base::FilePath GetPath() override;
      std::unique_ptr<content::ZoomLevelDelegate> CreateZoomLevelDelegate(
          const base::FilePath& partition_path) override;
      bool IsOffTheRecord() override;
      content::DownloadManagerDelegate* GetDownloadManagerDelegate() override;
      content::ResourceContext* GetResourceContext() override;
      content::BrowserPluginGuestManager* GetGuestManager() override;
      storage::SpecialStoragePolicy* GetSpecialStoragePolicy() override;
      content::PlatformNotificationService* GetPlatformNotificationService() override;
      content::PushMessagingService* GetPushMessagingService() override;
      content::StorageNotificationService* GetStorageNotificationService() override;
      content::SSLHostStateDelegate* GetSSLHostStateDelegate() override;
      content::PermissionControllerDelegate* GetPermissionControllerDelegate() override;
      content::BackgroundFetchDelegate* GetBackgroundFetchDelegate() override;
      content::BackgroundSyncController* GetBackgroundSyncController() override;
      content::BrowsingDataRemoverDelegate* GetBrowsingDataRemoverDelegate() override;
      content::ContentIndexProvider* GetContentIndexProvider() override;
      content::ClientHintsControllerDelegate* GetClientHintsControllerDelegate() override;


    protected:
      class ShellResourceContext : public content::ResourceContext {
        public:
          ShellResourceContext();

          ShellResourceContext(const ShellResourceContext&) = delete;
          ShellResourceContext& operator=(const ShellResourceContext&) = delete;

          ~ShellResourceContext() override;
      };

      std::unique_ptr<ShellResourceContext> resource_context_;

      std::unique_ptr<ShellDownloadManagerDelegate> download_manager_delegate_;

      std::unique_ptr<content::PermissionControllerDelegate> permission_manager_;

      std::unique_ptr<content::BackgroundSyncController> background_sync_controller_;

      std::unique_ptr<content::ContentIndexProvider> content_index_provider_;  

    private:
      const bool off_the_record_;

      base::FilePath path_;

      raw_ptr<content::ClientHintsControllerDelegate> client_hints_controller_delegate_ =
        nullptr;  
  };
}


#endif