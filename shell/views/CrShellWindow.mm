//
//  CrShellWindow.m
//  Cao
//
//  Created by 余圣源 on 2022/2/25.
//

#import "CrShellWindow.h"


@implementation CrShellWindow

- (instancetype)initWithContentRect:(NSRect)contentRect
                          styleMask:(NSUInteger)windowStyle
                            backing:(NSBackingStoreType)bufferingType
                              defer:(BOOL)deferCreation {
  self = [super initWithContentRect:contentRect
                          styleMask:windowStyle
                            backing:bufferingType
                             defer:deferCreation];
  return self;
}

@end
