#include "shell/browser/ui/cocoa/electron_inspectable_web_contents_view.h"

#include "content/public/browser/render_widget_host_view.h"
#include "shell/browser/ui/inspectable_web_contents_view_mac.h"

@implementation ElectronInspectableWebContentsView

- (instancetype)initWithInspectableWebContentsViewMac:
    (InspectableWebContentsViewMac*)view {
  self = [super init];
  if (!self)
    return nil;

  inspectableWebContentsView_ = view;
  devtools_visible_ = NO;
  devtools_docked_ = NO;
  devtools_is_first_responder_ = NO;
  attached_to_window_ = NO;

  auto* contents =
      inspectableWebContentsView_->inspectable_web_contents()->GetWebContents();
  auto* contentsView = contents->GetNativeView().GetNativeNSView();
  [contentsView setAutoresizingMask:NSViewWidthSizable | NSViewHeightSizable];
  [self addSubview:contentsView];
  [self setWantsLayer:YES];

  return self;
}

@end