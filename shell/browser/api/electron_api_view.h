#ifndef ELECTRON_SHELL_BROWSER_API_ELECTRON_API_VIEW_H_
#define ELECTRON_SHELL_BROWSER_API_ELECTRON_API_VIEW_H_

#include <vector>

#include "electron/buildflags/buildflags.h"
#include "gin/handle.h"
#include "ui/views/view.h"

#include "shell/common/gin_helper/wrappable.h"

namespace electron {

namespace api {
class View : public gin_helper::Wrappable<View> {
 public:
  static gin_helper::WrappableBase* New(gin::Arguments* args);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

  views::View* view() const { return view_; }

  // disable copy
  View(const View&) = delete;
  View& operator=(const View&) = delete;

 protected:
  explicit View(views::View* view);
  View();
  ~View() override;

  // Should delete the |view_| in destructor.
  void set_delete_view(bool should) { delete_view_ = should; }

 private:
  std::vector<v8::Global<v8::Object>> child_views_;

  bool delete_view_ = true;

  views::View* view_ = nullptr;
};
}  // namespace api
}  // namespace electron

#endif