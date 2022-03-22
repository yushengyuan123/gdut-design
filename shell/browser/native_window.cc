// Copyright (c) 2013 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "shell/browser/native_window.h"

#include <algorithm>
#include <string>
#include <vector>

#include "shell/browser/browser.h"
#include "shell/browser/window_list.h"
#include "shell/common/gin_helper/dictionary.h"

namespace electron {
namespace {}

NativeWindow::NativeWindow(const gin_helper::Dictionary& options,
                           NativeWindow* parent)
    : widget_(std::make_unique<views::Widget>()), parent_(parent) {
  WindowList::AddWindow(this);
}

NativeWindow::~NativeWindow() {
  // It's possible that the windows gets destroyed before it's closed, in that
  // case we need to ensure the Widget delegate gets destroyed and
  // OnWindowClosed message is still notified.
  // if (widget_->widget_delegate())
  //   widget_->OnNativeWidgetDestroyed();
  // NotifyWindowClosed();
}

void NativeWindow::NotifyWindowShow() {
  for (NativeWindowObserver& observer : observers_)
    observer.OnWindowShow();
}

gfx::Size NativeWindow::GetMinimumSize() const {
  return GetSizeConstraints().GetMinimumSize();
}

extensions::SizeConstraints NativeWindow::GetContentSizeConstraints() const {
  return size_constraints_;
}

extensions::SizeConstraints NativeWindow::GetSizeConstraints() const {
  extensions::SizeConstraints content_constraints = GetContentSizeConstraints();
  extensions::SizeConstraints window_constraints;
  if (content_constraints.HasMaximumSize()) {
    gfx::Rect max_bounds = ContentBoundsToWindowBounds(
        gfx::Rect(content_constraints.GetMaximumSize()));
    window_constraints.set_maximum_size(max_bounds.size());
  }
  if (content_constraints.HasMinimumSize()) {
    gfx::Rect min_bounds = ContentBoundsToWindowBounds(
        gfx::Rect(content_constraints.GetMinimumSize()));
    window_constraints.set_minimum_size(min_bounds.size());
  }
  return window_constraints;
}

gfx::Size NativeWindow::GetMaximumSize() const {
  return GetSizeConstraints().GetMaximumSize();
}

// static
// void NativeWindowRelay::CreateForWebContents(
//     content::WebContents* web_contents,
//     base::WeakPtr<NativeWindow> window) {
//   DCHECK(web_contents);
//   if (!web_contents->GetUserData(UserDataKey())) {
//     web_contents->SetUserData(
//         UserDataKey(),
//         base::WrapUnique(new NativeWindowRelay(web_contents, window)));
//   }
// }

// NativeWindowRelay::NativeWindowRelay(content::WebContents* web_contents,
//                                      base::WeakPtr<NativeWindow> window)
//     : content::WebContentsUserData<NativeWindowRelay>(*web_contents),
//       native_window_(window) {}

// NativeWindowRelay::~NativeWindowRelay() = default;

// WEB_CONTENTS_USER_DATA_KEY_IMPL(NativeWindowRelay);
}  // namespace electron