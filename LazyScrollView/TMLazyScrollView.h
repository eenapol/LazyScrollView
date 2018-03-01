//
//  TMLazyScrollView.h
//  LazyScrollView
//
//  Copyright (c) 2015-2018 Alibaba. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "TMLazyItemModel.h"

@class TMLazyScrollView;

@protocol TMLazyScrollViewDataSource <NSObject>

@required

/**
 Similar with 'tableView:numberOfRowsInSection:' of UITableView.
 */
- (NSUInteger)numberOfItemsInScrollView:(nonnull TMLazyScrollView *)scrollView;

/**
 Similar with 'tableView:heightForRowAtIndexPath:' of UITableView.
 Manager the correct muiID of item views will bring a higher performance.
 */
- (nonnull TMLazyItemModel *)scrollView:(nonnull TMLazyScrollView *)scrollView
                       itemModelAtIndex:(NSUInteger)index;

/**
 Similar with 'tableView:cellForRowAtIndexPath:' of UITableView.
 It will use muiID in item model instead of index.
 */
- (nonnull UIView *)scrollView:(nonnull TMLazyScrollView *)scrollView
                   itemByMuiID:(nonnull NSString *)muiID;

@end

//****************************************************************

@interface TMLazyScrollView : UIScrollView

@property (nonatomic, weak, nullable) id<TMLazyScrollViewDataSource> dataSource;

/**
 LazyScrollView can be used as a subview of another ScrollView.
 For example:
 You can use LazyScrollView as footerView of TableView.
 Then the outerScrollView should be that TableView.
 */
@property (nonatomic, weak, nullable) UIScrollView *outerScrollView;

/**
 If it is YES, LazyScrollView will add created item view into
 its subviews automatically.
 Default value is NO.
 */
@property (nonatomic, assign) BOOL autoAddSubview;

/**
 Item views which is in the buffer area.
 They will be shown soon.
 */
@property (nonatomic, strong, readonly, nonnull) NSSet<UIView *> *visibleItems;

/**
 Item views which is in the screen visible area.
 It is a sub set of "visibleItems".
 */
@property (nonatomic, strong, readonly, nonnull) NSSet<UIView *> *inScreenVisibleItems;

- (void)reloadData;

/**
 Get reuseable view by reuseIdentifier.
 */
- (nullable UIView *)dequeueReusableItemWithIdentifier:(nonnull NSString *)identifier;
/**
 Get reuseable view by reuseIdentifier and muiID.
 MuiID has higher priority.
 */
- (nullable UIView *)dequeueReusableItemWithIdentifier:(nonnull NSString *)identifier
                                                 muiID:(nullable NSString *)muiID;

- (void)clearItemViewsAndReusePool;
- (void)removeAllLayouts __deprecated_msg("use clearItemViewsAndReusePool");

/**
 After call this method, the times of 'mui_didEnterWithTimes:' will start from 0.
 */
- (void)resetItemViewsEnterTimes;
- (void)resetViewEnterTimes __deprecated_msg("use resetItemViewsEnterTimes");

@end

//****************************************************************

@interface TMLazyScrollViewObserver: NSObject

@property (nonatomic, weak, nullable) TMLazyScrollView *lazyScrollView;

@end