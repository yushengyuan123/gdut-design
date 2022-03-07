#ifndef ELECTRON_SHELL_BROWSER_NATIVE_WINDOW_MAC_H_
#define ELECTRON_SHELL_BROWSER_NATIVE_WINDOW_MAC_H_

#import <Cocoa/Cocoa.h>

#include <memory>
#include <queue>
#include <string>
#include <vector>

#include "base/mac/scoped_nsobject.h"
#include "shell/browser/native_window.h"
#include "ui/display/display_observer.h"
#include "ui/native_theme/native_theme_observer.h"
#include "ui/views/controls/native/native_view_host.h"

@class ElectronNSWindow;
@class ElectronNSWindowDelegate;
@class ElectronPreviewItem;

namespace electron {
  class RootViewMac;

  class NativeWindowMac : public NativeWindow,
                          public ui::NativeThemeObserver,
                          public display::DisplayObserver {
    public:
      NativeWindowMac(const gin_helper::Dictionary& options, NativeWindow* parent);
      ~NativeWindowMac() override;

      // NativeWindow:
      views::View* GetContentsView() override;

      gfx::Rect ContentBoundsToWindowBounds(const gfx::Rect& bounds) const override;

      // Use a custom content view instead of Chromium's BridgedContentView.
      void OverrideNSWindowContentView();

      gfx::NativeWindow GetNativeWindow() const override;
      
      void SetContentView(views::View* view) override;

      ElectronPreviewItem* preview_item() const { return preview_item_.get(); }


    protected:
      // ui::NativeThemeObserver:
      void OnNativeThemeUpdated(ui::NativeTheme* observed_theme) override;  
      
    private:
      base::scoped_nsobject<ElectronNSWindowDelegate> window_delegate_;

      base::scoped_nsobject<ElectronPreviewItem> preview_item_;

      std::unique_ptr<RootViewMac> root_view_;

      ElectronNSWindow* window_;  
  };
}

#endif