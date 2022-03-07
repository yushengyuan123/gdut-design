#include "shell/browser/ui/inspectable_web_contents.h"

#include <memory>
#include <utility>

namespace electron {

  namespace {
    InspectableWebContents::List g_web_contents_instances_;
  }

  InspectableWebContents::InspectableWebContents(
      std::unique_ptr<content::WebContents> web_contents,
      PrefService* pref_service,
      bool is_guest)
      : pref_service_(pref_service),
        web_contents_(std::move(web_contents)),
        is_guest_(is_guest),
        view_(CreateInspectableContentsView(this)) {

    g_web_contents_instances_.push_back(this);
  }

  InspectableWebContents::~InspectableWebContents() {

  }

  // Implemented separately on each platform.
  InspectableWebContentsView* CreateInspectableContentsView(
      InspectableWebContents* inspectable_web_contents);

  bool InspectableWebContents::IsGuest() const {
    return is_guest_;
  }
}