#ifndef ELECTRON_SHELL_BROWSER_API_ELECTRON_API_VIEW_H_
#define ELECTRON_SHELL_BROWSER_API_ELECTRON_API_VIEW_H_

#include <vector>

#include "electron/buildflags/buildflags.h"
#include "gin/handle.h"
#include "ui/views/view.h"

namespace electron {

namespace api {
class View : public views::View {
 public:
  views::View* view() const { return view_; }

  // disable copy
  View(const View&) = delete;
  View& operator=(const View&) = delete;

 protected:
  explicit View(views::View* view);
  View();
  ~View() override;

 private:
  bool delete_view_ = true;
  views::View* view_ = nullptr;
};
}  // namespace api
}  // namespace electron

#endif