// Copyright (c) 2013 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#import "shell/browser/mac/electron_application.h"
#import "stdio.h"


@implementation AtomApplication
+ (AtomApplication*)sharedApplication {
	return (AtomApplication*)[super sharedApplication];
}
@end
