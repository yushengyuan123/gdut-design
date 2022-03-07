
#include "shell/browser/api/electron_api_view.h"

#include "shell/common/gin_helper/dictionary.h"

namespace electron {

  namespace api {
    View::View(views::View* view) : view_(view) {
      view_->set_owned_by_client();
    }

    View::View() : View(new views::View()) {}

    View::~View() {
      if (delete_view_)
        delete view_;
    }
  }

}