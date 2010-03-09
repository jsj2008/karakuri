//
//  BXResourceElement.m
//  Karakuri Box
//
//  Created by numata on 10/02/27.
//  Copyright 2010 Apple Inc. All rights reserved.
//

#import "BXResourceElement.h"


@interface BXResourceElement ()

- (void)setParent:(BXResourceElement*)anElem;

@end


@implementation BXResourceElement

#pragma mark -
#pragma mark 初期化・クリーンアップ

- (id)initWithName:(NSString*)name
{
    self = [super init];
    if (self) {
        mName = [name copy];
        mChildElements = [[NSMutableArray alloc] init];
        
        mResourceID = 99;   // TODO: リソースIDをちゃんと管理する。
    }
    return self;
}

- (void)dealloc
{
    [mName release];
    [mChildElements release];

    [super dealloc];
}


#pragma mark -
#pragma mark 項目の管理

- (NSString*)localizedName
{
    if ([mName hasPrefix:@"*"]) {
        return NSLocalizedString(mName, nil);
    }
    return [NSString stringWithFormat:@"%d: %@", mResourceID, mName];
}

- (BOOL)isExpandable
{
    return NO;
}

- (BOOL)isGroupItem
{
    return NO;
}

- (int)resourceID
{
    return mResourceID;
}

- (NSString*)resourceName
{
    return mName;
}

- (void)setResourceID:(int)theID
{
    mResourceID = theID;
    
    if (mParentElement) {
        [mParentElement sortChildrenByResourceID];
    }
}

- (void)setResourceName:(NSString*)name
{
    [mName release];
    mName = [name copy];
}


#pragma mark -
#pragma mark 子供の管理

- (void)addChild:(BXResourceElement*)anElem
{
    [anElem setParent:self];
    [mChildElements addObject:anElem];
}

- (int)childCount
{
    return [mChildElements count];
}

- (BXResourceElement*)childAtIndex:(int)index
{
    return [mChildElements objectAtIndex:index];
}

- (void)removeChild:(BXResourceElement*)anElem
{
    [anElem setParent:nil];
    [mChildElements removeObject:anElem];
}

- (void)setParent:(BXResourceElement*)anElem
{
    mParentElement = anElem;
}

- (void)sortChildrenByResourceID
{
    NSSortDescriptor* sortDesc = [[[NSSortDescriptor alloc] initWithKey:@"resourceID"
                                                              ascending:YES] autorelease];

    [mChildElements sortUsingDescriptors:[NSArray arrayWithObject:sortDesc]];
}

- (NSString*)description
{
    return [self localizedName];
}

@end
