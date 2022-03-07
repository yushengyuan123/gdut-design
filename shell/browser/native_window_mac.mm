#include "shell/browser/native_window_mac.h"

#include "shell/browser/native_window.h"
#include "shell/browser/ui/cocoa/electron_native_widget_mac.h"
#include "shell/browser/ui/cocoa/electron_ns_window.h"
#include "shell/browser/ui/cocoa/electron_ns_window_delegate.h"
#include "shell/browser/ui/cocoa/root_view_mac.h"
#include "shell/common/gin_helper/dictionary.h"
#include "ui/display/screen.h"
#include "ui/views/cocoa/native_widget_mac_ns_window_host.h"

#include "ui/views/widget/widget.h"

namespace electron {
  NativeWindowMac::NativeWindowMac(const gin_helper::Dictionary& options,
                                    NativeWindow* parent)
      : NativeWindow(options, parent), root_view_(new RootViewMac(this)) {
    display::Screen::GetScreen()->AddObserver(this);

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

  }

  void NativeWindowMac::OnNativeThemeUpdated(ui::NativeTheme* observed_theme) {

  }

  void NativeWindowMac::SetContentView(views::View* view) {
    views::View* root_view = GetContentsView();
    if (content_view())
      root_view->RemoveChildView(content_view());

    set_content_view(view);
    root_view->AddChildView(content_view());

    root_view->Layout();
  }

  void NativeWindowMac::OverrideNSWindowContentView() {
    // 暂时不懂干什么的
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