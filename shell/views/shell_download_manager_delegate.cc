// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "shell/views/shell_download_manager_delegate.h"

#include <string>

#if defined(OS_WIN)
#include <windows.h>
#include <commdlg.h>
#endif

#include "base/bind.h"
#include "base/check_op.h"
#include "base/command_line.h"
#include "base/cxx17_backports.h"
#include "base/files/file_util.h"
#include "base/notreached.h"
#include "base/strings/string_util.h"
#include "base/strings/utf_string_conversions.h"
#include "base/task/thread_pool.h"
#include "build/build_config.h"
#include "content/public/browser/browser_context.h"
#include "content/public/browser/browser_task_traits.h"
#include "content/public/browser/browser_thread.h"
#include "content/public/browser/download_item_utils.h"
#include "content/public/browser/download_manager.h"
#include "content/public/browser/web_contents.h"
#include "shell/views/shell_switches.h"
#include "net/base/filename_util.h"

#if defined(OS_WIN)
#include "ui/aura/window.h"
#include "ui/aura/window_tree_host.h"
#endif

namespace electron {

ShellDownloadManagerDelegate::ShellDownloadManagerDelegate()
    : download_manager_(nullptr), suppress_prompting_(false) {}

ShellDownloadManagerDelegate::~ShellDownloadManagerDelegate() {
  if (download_manager_) {
    download_manager_->SetDelegate(nullptr);
    download_manager_ = nullptr;
  }
}


void ShellDownloadManagerDelegate::SetDownloadManager(
    content::DownloadManager* download_manager) {
  download_manager_ = download_manager;
}

void ShellDownloadManagerDelegate::Shutdown() {
  // Revoke any pending callbacks. download_manager_ et. al. are no longer safe
  // to access after this point.
  weak_ptr_factory_.InvalidateWeakPtrs();
  download_manager_ = nullptr;
}

bool ShellDownloadManagerDelegate::DetermineDownloadTarget(
    download::DownloadItem* download,
    content::DownloadTargetCallback* callback) {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
  // This assignment needs to be here because even at the call to
  // SetDownloadManager, the system is not fully initialized.
  if (default_download_path_.empty()) {
    default_download_path_ = download_manager_->GetBrowserContext()->GetPath().
        Append(FILE_PATH_LITERAL("Downloads"));
  }

  if (!download->GetForcedFilePath().empty()) {
    std::move(*callback).Run(
        download->GetForcedFilePath(),
        download::DownloadItem::TARGET_DISPOSITION_OVERWRITE,
        download::DOWNLOAD_DANGER_TYPE_NOT_DANGEROUS,
        download::DownloadItem::MixedContentStatus::UNKNOWN,
        download->GetForcedFilePath(), absl::nullopt /*download_schedule*/,
        download::DOWNLOAD_INTERRUPT_REASON_NONE);
    return true;
  }

  FilenameDeterminedCallback filename_determined_callback = base::BindOnce(
      &ShellDownloadManagerDelegate::OnDownloadPathGenerated,
      weak_ptr_factory_.GetWeakPtr(), download->GetId(), std::move(*callback));

  base::ThreadPool::PostTask(
      FROM_HERE,
      {base::MayBlock(), base::TaskShutdownBehavior::SKIP_ON_SHUTDOWN,
       base::TaskPriority::USER_VISIBLE},
      base::BindOnce(&ShellDownloadManagerDelegate::GenerateFilename,
                     download->GetURL(), download->GetContentDisposition(),
                     download->GetSuggestedFilename(), download->GetMimeType(),
                     default_download_path_,
                     std::move(filename_determined_callback)));
  return true;
}

bool ShellDownloadManagerDelegate::ShouldOpenDownload(
    download::DownloadItem* item,
    content::DownloadOpenDelayedCallback callback) {
  return true;
}

void ShellDownloadManagerDelegate::GetNextId(content::DownloadIdCallback callback) {
  static uint32_t next_id = download::DownloadItem::kInvalidId + 1;
  std::move(callback).Run(next_id++);
}

// static
void ShellDownloadManagerDelegate::GenerateFilename(
    const GURL& url,
    const std::string& content_disposition,
    const std::string& suggested_filename,
    const std::string& mime_type,
    const base::FilePath& suggested_directory,
    FilenameDeterminedCallback callback) {
  base::FilePath generated_name = net::GenerateFileName(url,
                                                        content_disposition,
                                                        std::string(),
                                                        suggested_filename,
                                                        mime_type,
                                                        "download");

  if (!base::PathExists(suggested_directory))
    base::CreateDirectory(suggested_directory);

  base::FilePath suggested_path(suggested_directory.Append(generated_name));
  content::GetUIThreadTaskRunner({})->PostTask(
      FROM_HERE, base::BindOnce(std::move(callback), suggested_path));
}

void ShellDownloadManagerDelegate::OnDownloadPathGenerated(
    uint32_t download_id,
    content::DownloadTargetCallback callback,
    const base::FilePath& suggested_path) {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
  if (suppress_prompting_) {
    // Testing exit.
    std::move(callback).Run(
        suggested_path, download::DownloadItem::TARGET_DISPOSITION_OVERWRITE,
        download::DOWNLOAD_DANGER_TYPE_NOT_DANGEROUS,
        download::DownloadItem::MixedContentStatus::UNKNOWN,
        suggested_path.AddExtension(FILE_PATH_LITERAL(".crdownload")),
        absl::nullopt /*download_schedule*/,
        download::DOWNLOAD_INTERRUPT_REASON_NONE);
    return;
  }

  ChooseDownloadPath(download_id, std::move(callback), suggested_path);
}

void ShellDownloadManagerDelegate::ChooseDownloadPath(
    uint32_t download_id,
    content::DownloadTargetCallback callback,
    const base::FilePath& suggested_path) {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
  download::DownloadItem* item = download_manager_->GetDownload(download_id);
  if (!item || (item->GetState() != download::DownloadItem::IN_PROGRESS))
    return;

  base::FilePath result;

  std::move(callback).Run(result,
                          download::DownloadItem::TARGET_DISPOSITION_PROMPT,
                          download::DOWNLOAD_DANGER_TYPE_NOT_DANGEROUS,
                          download::DownloadItem::MixedContentStatus::UNKNOWN,
                          result, absl::nullopt /*download_schedule*/,
                          download::DOWNLOAD_INTERRUPT_REASON_NONE);
}

void ShellDownloadManagerDelegate::SetDownloadBehaviorForTesting(
    const base::FilePath& default_download_path) {
  default_download_path_ = default_download_path;
  suppress_prompting_ = true;
}

}  // namespace content
