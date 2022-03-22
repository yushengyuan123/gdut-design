// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_SHELL_BROWSER_SHELL_DOWNLOAD_MANAGER_DELEGATE_H_
#define CONTENT_SHELL_BROWSER_SHELL_DOWNLOAD_MANAGER_DELEGATE_H_

#include <stdint.h>

#include "base/callback_forward.h"
#include "base/memory/raw_ptr.h"
#include "base/memory/weak_ptr.h"
#include "content/public/browser/download_manager_delegate.h"

namespace content {
class DownloadManager;
}

namespace electron {


class ElectronDownloadManagerDelegate : public content::DownloadManagerDelegate {
 public:
  ElectronDownloadManagerDelegate();

  ElectronDownloadManagerDelegate(const ElectronDownloadManagerDelegate&) = delete;
  ElectronDownloadManagerDelegate& operator=(const ElectronDownloadManagerDelegate&) =
      delete;

  ~ElectronDownloadManagerDelegate() override;

  void SetDownloadManager(content::DownloadManager* manager);

  void Shutdown() override;
  bool DetermineDownloadTarget(download::DownloadItem* download,
                               content::DownloadTargetCallback* callback) override;
  bool ShouldOpenDownload(download::DownloadItem* item,
                          content::DownloadOpenDelayedCallback callback) override;
  void GetNextId(content::DownloadIdCallback callback) override;

  // Inhibits prompting and sets the default download path.
  void SetDownloadBehaviorForTesting(
      const base::FilePath& default_download_path);

 private:
  friend class base::RefCountedThreadSafe<ElectronDownloadManagerDelegate>;

  using FilenameDeterminedCallback =
      base::OnceCallback<void(const base::FilePath&)>;

  static void GenerateFilename(const GURL& url,
                               const std::string& content_disposition,
                               const std::string& suggested_filename,
                               const std::string& mime_type,
                               const base::FilePath& suggested_directory,
                               FilenameDeterminedCallback callback);
  void OnDownloadPathGenerated(uint32_t download_id,
                               content::DownloadTargetCallback callback,
                               const base::FilePath& suggested_path);
  void ChooseDownloadPath(uint32_t download_id,
                          content::DownloadTargetCallback callback,
                          const base::FilePath& suggested_path);

  raw_ptr<content::DownloadManager> download_manager_;
  base::FilePath default_download_path_;
  bool suppress_prompting_;
  base::WeakPtrFactory<ElectronDownloadManagerDelegate> weak_ptr_factory_{this};
};

}  // namespace content

#endif  // CONTENT_SHELL_BROWSER_SHELL_DOWNLOAD_MANAGER_DELEGATE_H_