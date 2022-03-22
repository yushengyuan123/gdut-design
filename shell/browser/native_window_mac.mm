#include "shell/browser/native_window_mac.h"

#include <AvailabilityMacros.h>
#include <objc/objc-runtime.h>


#include <algorithm>
#include <string>
#include <utility>
#include <vector>

#include "base/cxx17_backports.h"
#include "base/mac/mac_util.h"
#include "base/mac/scoped_cftyperef.h"
#include "base/strings/sys_string_conversions.h"
#include "base/task/post_task.h"
#include "components/remote_cocoa/app_shim/native_widget_ns_window_bridge.h"
#include "components/remote_cocoa/browser/scoped_cg_window_id.h"
#include "content/public/browser/browser_accessibility_state.h"
#include "content/public/browser/browser_task_traits.h"
#include "content/public/browser/browser_thread.h"
#include "content/public/browser/desktop_media_id.h"

#include "shell/browser/native_window.h"
#include "shell/browser/ui/cocoa/electron_native_widget_mac.h"
#include "shell/browser/ui/cocoa/electron_ns_window.h"
#include "shell/browser/ui/cocoa/electron_ns_window_delegate.h"
#include "shell/browser/ui/cocoa/root_view_mac.h"
#include "shell/common/gin_helper/dictionary.h"
#include "skia/ext/skia_utils_mac.h"
#include "third_party/webrtc/modules/desktop_capture/mac/window_list_utils.h"

#include "ui/display/screen.h"
#include "ui/gfx/skia_util.h"
#include "ui/gl/gpu_switching_manager.h"
#include "ui/views/background.h"
#include "ui/views/cocoa/native_widget_mac_ns_window_host.h"
#include "ui/views/widget/widget.h"

@interface ElectronAdaptedContentView : NSView {
 @private
  views::NativeWidgetMacNSWindowHost* bridge_host_;
}
@end

@implementation ElectronAdaptedContentView

- (id)initWithShell:(electron::NativeWindowMac*)shell {
  if ((self = [self init])) {
    bridge_host_ = views::NativeWidgetMacNSWindowHost::GetFromNativeWindow(
        shell->GetNativeWindow());
  }
  return self;
}

- (void)viewDidMoveToWindow {
  // When this view is added to a window, AppKit calls setFrameSize before it is
  // added to the window, so the behavior in setFrameSize is not triggered.
  NSWindow* window = [self window];
  if (window)
    [self setFrameSize:NSZeroSize];
}

- (void)setFrameSize:(NSSize)newSize {
  // The size passed in here does not always use
  // -[NSWindow contentRectForFrameRect]. The following ensures that the
  // contentView for a frameless window can extend over the titlebar of the new
  // window containing it, since AppKit requires a titlebar to give frameless
  // windows correct shadows and rounded corners.
  NSWindow* window = [self window];
  if (window && [window contentView] == self) {
    newSize = [window contentRectForFrameRect:[window frame]].size;
    // Ensure that the window geometry be updated on the host side before the
    // view size is updated.
    bridge_host_->GetInProcessNSWindowBridge()->UpdateWindowGeometry();
  }

  [super setFrameSize:newSize];

  // The OnViewSizeChanged is marked private in derived class.
  static_cast<remote_cocoa::mojom::NativeWidgetNSWindowHost*>(bridge_host_)
      ->OnViewSizeChanged(gfx::Size(newSize.width, newSize.height));
}

@end

namespace electron {
namespace {
bool IsFramelessWindow(NSView* view) {
  NSWindow* nswindow = [view window];
  if (![nswindow respondsToSelector:@selector(shell)])
    return false;
  NativeWindow* window = [static_cast<ElectronNSWindow*>(nswindow) shell];
  return window && !window->has_frame();
}

IMP original_set_frame_size = nullptr;
IMP original_view_did_move_to_superview = nullptr;
}

NativeWindowMac::NativeWindowMac(const gin_helper::Dictionary& options,
                                 NativeWindow* parent)
    : NativeWindow(options, parent), root_view_(new RootViewMac(this)) {
  // display::Screen::GetScreen()->AddObserver(this);

  int width = 800, height = 600;
  // options.Get(options::kWidth, &width);
  // options.Get(options::kHeight, &height);

  NSRect main_screen_rect = [[[NSScreen screens] firstObject] frame];
  gfx::Rect bounds(round((NSWidth(main_screen_rect) - width) / 2),
                   round((NSHeight(main_screen_rect) - height) / 2), width,
                   height);

  NSUInteger styleMask = NSWindowStyleMaskTitled;
  bool resizable = true;
  bool minimizable = true;
  // bool rounded_corner = true;
  // bool maximizable = true;
  bool closable = true;

  if (minimizable)
    styleMask |= NSMiniaturizableWindowMask;
  if (closable)
    styleMask |= NSWindowStyleMaskClosable;
  if (resizable)
    styleMask |= NSResizableWindowMask;

  views::Widget::InitParams params;
  params.ownership = views::Widget::InitParams::WIDGET_OWNS_NATIVE_WIDGET;
  params.bounds = bounds;
  params.delegate = this;
  params.type = views::Widget::InitParams::TYPE_WINDOW;
  params.native_widget = new ElectronNativeWidgetMac(this, styleMask, widget());
  widget()->Init(std::move(params));
  window_ = static_cast<ElectronNSWindow*>(
      widget()->GetNativeWindow().GetNativeNSWindow());
  window_delegate_.reset([[ElectronNSWindowDelegate alloc] initWithShell:this]);
  // Default content view.
  SetContentView(new views::View());
  AddContentViewLayers();

}

void NativeWindowMac::OnNativeThemeUpdated(ui::NativeTheme* observed_theme) {}

void NativeWindowMac::SetContentView(views::View* view) {
  views::View* root_view = GetContentsView();
  if (content_view())
    root_view->RemoveChildView(content_view());

  set_content_view(view);
  root_view->AddChildView(content_view());

  root_view->Layout();
}

void NativeWindowMac::Show() {
  [window_ makeKeyAndOrderFront:nil];
}

void NativeWindowMac::OverrideNSWindowContentView() {
  container_view_.reset(
      [[ElectronAdaptedContentView alloc] initWithShell:this]);

  [container_view_
      setAutoresizingMask:NSViewWidthSizable | NSViewHeightSizable];
  [window_ setContentView:container_view_];
  AddContentViewLayers();

  // [window_ makeKeyAndOrderFront:nil];
}

// This is less than ideal, and should eventually be removed.
void ViewDidMoveToSuperview(NSView* self, SEL _cmd) {
  if (!IsFramelessWindow(self)) {
    // [BridgedContentView viewDidMoveToSuperview];
    auto original = reinterpret_cast<decltype(&ViewDidMoveToSuperview)>(
        original_view_did_move_to_superview);
    if (original)
      original(self, _cmd);
    return;
  }
  [self setFrame:[[self superview] bounds]];
}

void SetFrameSize(NSView* self, SEL _cmd, NSSize size) {
  if (!IsFramelessWindow(self)) {
    auto original =
        reinterpret_cast<decltype(&SetFrameSize)>(original_set_frame_size);
    return original(self, _cmd, size);
  }
  // For frameless window, resize the view to cover full window.
  if ([self superview])
    size = [[self superview] bounds].size;
  auto super_impl = reinterpret_cast<decltype(&SetFrameSize)>(
      [[self superclass] instanceMethodForSelector:_cmd]);
  super_impl(self, _cmd, size);
}

void NativeWindowMac::AddContentViewLayers() {
  // Make sure the bottom corner is rounded for non-modal windows:
  // http://crbug.com/396264.
  if (!is_modal()) {
    // For normal window, we need to explicitly set layer for contentView to
    // make setBackgroundColor work correctly.
    // There is no need to do so for frameless window, and doing so would make
    // titleBarStyle stop working.
    if (has_frame()) {
      base::scoped_nsobject<CALayer> background_layer([[CALayer alloc] init]);
      [background_layer
          setAutoresizingMask:kCALayerWidthSizable | kCALayerHeightSizable];
      [[window_ contentView] setLayer:background_layer];
    }
    [[window_ contentView] setWantsLayer:YES];
  }

  if (!has_frame()) {
    // In OSX 10.10, adding subviews to the root view for the NSView hierarchy
    // produces warnings. To eliminate the warnings, we resize the contentView
    // to fill the window, and add subviews to that.
    // http://crbug.com/380412
    if (!original_set_frame_size) {
      Class cl = [[window_ contentView] class];
      original_set_frame_size = class_replaceMethod(
          cl, @selector(setFrameSize:), (IMP)SetFrameSize, "v@:{_NSSize=ff}");
      original_view_did_move_to_superview =
          class_replaceMethod(cl, @selector(viewDidMoveToSuperview),
                              (IMP)ViewDidMoveToSuperview, "v@:");
      [[window_ contentView] viewDidMoveToWindow];
    }
  }
}

views::View* NativeWindowMac::GetContentsView() {
  return root_view_.get();
}

gfx::NativeWindow NativeWindowMac::GetNativeWindow() const {
  return window_;
}

gfx::Rect NativeWindowMac::ContentBoundsToWindowBounds(
    const gfx::Rect& bounds) const {
  if (has_frame()) {
    gfx::Rect window_bounds(
        [window_ frameRectForContentRect:bounds.ToCGRect()]);
    int frame_height = window_bounds.height() - bounds.height();
    window_bounds.set_y(window_bounds.y() - frame_height);
    return window_bounds;
  } else {
    return bounds;
  }
}

// static
NativeWindow* NativeWindow::Create(const gin_helper::Dictionary& options,
                                   NativeWindow* parent) {
  return new NativeWindowMac(options, parent);
}

NativeWindowMac::~NativeWindowMac() = default;
}