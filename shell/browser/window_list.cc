#include "shell/browser/window_list.h"

#include <algorithm>

#include "base/logging.h"
#include "shell/browser/native_window.h"
#include "shell/browser/window_list_observer.h"

namespace electron {
  // static
  base::LazyInstance<base::ObserverList<WindowListObserver>>::Leaky
      WindowList::observers_ = LAZY_INSTANCE_INITIALIZER;

  // static
  WindowList* WindowList::instance_ = nullptr;    

  // static
  void WindowList::AddWindow(NativeWindow* window) {
    DCHECK(window);
    // Push |window| on the appropriate list instance.
    WindowVector& windows = GetInstance()->windows_;
    windows.push_back(window);

    for (WindowListObserver& observer : observers_.Get())
      observer.OnWindowAdded(window);
  }

  // static
  void WindowList::RemoveWindow(NativeWindow* window) {
    WindowVector& windows = GetInstance()->windows_;
    windows.erase(std::remove(windows.begin(), windows.end(), window),
                  windows.end());

    for (WindowListObserver& observer : observers_.Get())
      observer.OnWindowRemoved(window);

    if (windows.empty()) {
      for (WindowListObserver& observer : observers_.Get())
        observer.OnWindowAllClosed();
    }
  } 

  // static
  WindowList* WindowList::GetInstance() {
    if (!instance_)
      instance_ = new WindowList;
    return instance_;
  } 

  WindowList::WindowList() = default;

  WindowList::~WindowList() = default;
}