
#include "shell/browser/ui/inspectable_web_contents.h"

#include <memory>
#include <utility>

#include "shell/browser/ui/inspectable_web_contents_view.h"


namespace electron {
namespace {
// Stores all instances of InspectableWebContents.
InspectableWebContents::List g_web_contents_instances_;
}

// Implemented separately on each platform.
// 这个函数可能就是窗体开启的入口了
InspectableWebContentsView* CreateInspectableContentsView(
    InspectableWebContents* inspectable_web_contents);

// 这个东西什么时候被初始化的呢？？
InspectableWebContents::InspectableWebContents(
    std::unique_ptr<content::WebContents> web_contents,
    bool is_guest)
    : web_contents_(std::move(web_contents)),
      is_guest_(is_guest),
      view_(CreateInspectableContentsView(this)) {

  if (is_guest_) {
    printf("is_guest true\n");
  }  

  printf("InspectableWebContents初始化\n");    

  g_web_contents_instances_.push_back(this);
}

InspectableWebContents::~InspectableWebContents() {

}

content::WebContents* InspectableWebContents::GetWebContents() const {
  return web_contents_.get();
}

InspectableWebContentsView* InspectableWebContents::GetView() const {
  printf("InspectableWebContents GetView\n");

  InspectableWebContentsView* a = view_.get();

  printf("InspectableWebContents GetView111\n");
  return a;
}

}  // namespace electron