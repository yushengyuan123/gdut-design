#ifndef ELECTRON_SHELL_BROWSER_BROWSER_H_
#define ELECTRON_SHELL_BROWSER_BROWSER_H_

#include <memory>
#include <string>
#include <vector>

#include "base/observer_list.h"
#include "shell/browser/browser_observer.h"
#include "shell/browser/window_list_observer.h"

// 既然这个browser类实现了这个WindowListObserver类，那么当WindowList中有window发生了变化自然执行的就是这里的
// 实现方法
// 这个browser类很多的方法都是没有实现的，估计也是被别人用的一个类

// 整理一下这里多个观察者类的一个依赖关系
// browser类依赖了WindowListObserver（不知道继承他有什么作用？？作用在于让他是WindowListObserver类型，在windowList的add方法中参数要求是这个类型），
// 这个browser类在实例化的时候会把自己加入windowList
// 他自己有一个BrowserObserver的ObserverList，他有add方法把BrowserObserver加入到这个list中（暂时不知道别的地方调用它）
// windowList有一个WindowListObserver的ObserverList。他的add方法是加入NativeWindow到它自己这里


// 这里面有一个很妖的逻辑：
// 在browser实例化的时候调用了WindowList::AddObserver(this);
// 而AddObserver = observers_.Get().AddObserver(browser);
// 就把这browser实例加入到observers_ list中
namespace electron {
  class Browser : public WindowListObserver {
    public:
      Browser();
      ~Browser() override;  

      // disable copy
      Browser(const Browser&) = delete;
      Browser& operator=(const Browser&) = delete;  

      // 这个东西是获得ElectronBrowserMainParts
      static Browser* Get();

      // Try to close all windows and quit the application.
      void Quit();

      // Cleanup everything and shutdown the application gracefully.
      void Shutdown();

      void AddObserver(BrowserObserver* obs) { observers_.AddObserver(obs); }

      void RemoveObserver(BrowserObserver* obs) { observers_.RemoveObserver(obs); }

      

    protected:
      // Send the will-quit message and then shutdown the application.
      void NotifyAndShutdown();

      // Send the before-quit message and start closing windows.
      bool HandleBeforeQuit();

      bool is_quitting_ = false;


    private:
      // Observers of the browser.
      base::ObserverList<BrowserObserver> observers_;

      // The browser is being shutdown.
      bool is_shutdown_ = false;        
  }
}


#endif  // ELECTRON_SHELL_BROWSER_BROWSER_H_