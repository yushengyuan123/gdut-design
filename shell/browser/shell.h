// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
#ifndef CONTENT_SHELL_BROWSER_SHELL_H_
#define CONTENT_SHELL_BROWSER_SHELL_H_

#include <stdint.h>

#include <memory>
#include <string>
#include <vector>

#include "content/public/browser/web_contents_delegate.h"
#include "content/public/browser/web_contents_observer.h"
#include "shell/browser/shell_platform_delegate.h"
#include "content/public/browser/site_instance.h"
#include "content/public/browser/web_contents.h"

class GURL;

namespace electron {
  class Shell : public content::WebContentsDelegate, content::WebContentsObserver {
    public:
      ~Shell() override;
      void LoadURL(const GURL& url);
      void LoadURLForFrame(const GURL& url,
                       const std::string& frame_name,
                       ui::PageTransition);

      static Shell* CreateNewWindow(
        content::BrowserContext* browser_context,
        const GURL& url,
        const scoped_refptr<content::SiteInstance>& site_instance);

    private:
      Shell(std::unique_ptr<content::WebContents> web_contents); 

      // Helper to create a new Shell given a newly created WebContents.
      static Shell* CreateShell(std::unique_ptr<content::WebContents> web_contents);

      std::unique_ptr<content::WebContents> web_contents_;                    
  };
}


#endif