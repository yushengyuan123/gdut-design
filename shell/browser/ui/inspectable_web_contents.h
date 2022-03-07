#ifndef ELECTRON_SHELL_BROWSER_UI_INSPECTABLE_WEB_CONTENTS_H_
#define ELECTRON_SHELL_BROWSER_UI_INSPECTABLE_WEB_CONTENTS_H_

#include <list>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include "base/containers/span.h"
#include "base/containers/unique_ptr_adapters.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/devtools/devtools_contents_resizing_strategy.h"
#include "chrome/browser/devtools/devtools_embedder_message_dispatcher.h"
#include "chrome/browser/devtools/devtools_settings.h"
#include "content/public/browser/devtools_agent_host.h"
#include "content/public/browser/devtools_frontend_host.h"
#include "content/public/browser/web_contents_delegate.h"
#include "content/public/browser/web_contents_observer.h"
#include "electron/buildflags/buildflags.h"
#include "ui/gfx/geometry/rect.h"

namespace electron {
    class InspectableWebContents
        : public content::DevToolsAgentHostClient,
        public content::WebContentsObserver,
        public content::WebContentsDelegate,
        public DevToolsEmbedderMessageDispatcher::Delegate {
        
        public:
            using List = std::list<InspectableWebContents*>;

            InspectableWebContents(std::unique_ptr<content::WebContents> web_contents,
                                    PrefService* pref_service,
                                    bool is_guest);
            ~InspectableWebContents() override;

            // disable copy
            InspectableWebContents(const InspectableWebContents&) = delete;
            InspectableWebContents& operator=(const InspectableWebContents&) = delete;

            bool IsGuest() const;

        private:
            PrefService* pref_service_;  // weak reference.

            std::unique_ptr<content::WebContents> web_contents_;

            bool is_guest_;

            std::unique_ptr<InspectableWebContentsView> view_;    
    
    };
}


#endif