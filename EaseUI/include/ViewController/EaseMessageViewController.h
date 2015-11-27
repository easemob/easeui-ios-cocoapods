//
//  EaseMessageViewController.h
//  ChatDemo-UI3.0
//
//  Created by dhc on 15/6/26.
//  Copyright (c) 2015年 easemob.com. All rights reserved.
//

#import <MobileCoreServices/MobileCoreServices.h>
#import <AVFoundation/AVFoundation.h>
#import <MediaPlayer/MediaPlayer.h>
#import "EaseRefreshTableViewController.h"

#import "IMessageModel.h"
#import "EaseMessageModel.h"
#import "EaseBaseMessageCell.h"
#import "EaseMessageTimeCell.h"
#import "EaseChatToolbar.h"
#import "EaseLocationViewController.h"
#import "EMCDDeviceManager+Media.h"
#import "EMCDDeviceManager+ProximitySensor.h"
#import "UIViewController+HUD.h"
#import "EaseSDKHelper.h"

@class EaseMessageViewController;

@protocol EaseMessageViewControllerDelegate <NSObject>

@optional

/*!
 @method
 @brief 获取消息自定义cell
 @discussion 用户根据messageModel判断是否显示自定义cell,返回nil显示默认cell,否则显示用户自定义cell
 @param tableView 当前消息视图的tableView
 @param messageModel 消息模型
 @result 返回用户自定义cell
 */
- (UITableViewCell *)messageViewController:(UITableView *)tableView
                       cellForMessageModel:(id<IMessageModel>)messageModel;

/*!
 @method
 @brief 获取消息cell高度
 @discussion 用户根据messageModel判断,是否自定义显示cell的高度
 @param viewController 当前消息视图
 @param messageModel 消息模型
 @param cellWidth 视图宽度
 @result 返回用户自定义cell
 */
- (CGFloat)messageViewController:(EaseMessageViewController *)viewController
           heightForMessageModel:(id<IMessageModel>)messageModel
                   withCellWidth:(CGFloat)cellWidth;

/**
 *  发送消息成功
 */
- (void)messageViewController:(EaseMessageViewController *)viewController
          didSendMessageModel:(id<IMessageModel>)messageModel;

/**
 *  发送消息失败
 */
- (void)messageViewController:(EaseMessageViewController *)viewController
   didFailSendingMessageModel:(id<IMessageModel>)messageModel
                        error:(EMError *)error;

/**
 *  接收到消息的已读回执
 */
- (void)messageViewController:(EaseMessageViewController *)viewController
 didReceiveHasReadAckForModel:(id<IMessageModel>)messageModel;

/**
 *  选中消息
 */
- (BOOL)messageViewController:(EaseMessageViewController *)viewController
        didSelectMessageModel:(id<IMessageModel>)messageModel;

/*!
 @method
 @brief 点击消息头像
 @discussion 获取用户点击头像回调
 @param viewController 当前消息视图
 @param messageModel 消息模型
 @result
 */
- (void)messageViewController:(EaseMessageViewController *)viewController
    didSelectAvatarMessageModel:(id<IMessageModel>)messageModel;

/**
 *  选中底部功能按钮
 */
- (void)messageViewController:(EaseMessageViewController *)viewController
            didSelectMoreView:(EaseChatBarMoreView *)moreView
                      AtIndex:(NSInteger)index;

/*!
 @method
 @brief 底部录音功能按钮状态回调
 @discussion 获取底部录音功能按钮状态回调,根据EaseRecordViewType,用户自定义处理UI的逻辑
 @param viewController 当前消息视图
 @param recordView 录音视图
 @param type 录音按钮当前状态
 @result
 */
- (void)messageViewController:(EaseMessageViewController *)viewController
              didSelectRecordView:(UIView *)recordView
                withEvenType:(EaseRecordViewType)type;
@end


@protocol EaseMessageViewControllerDataSource <NSObject>

@optional

/**
 *  指定消息附件上传或者下载进度的监听者， 默认self
 */
- (id<IEMChatProgressDelegate>)messageViewController:(EaseMessageViewController *)viewController
                  progressDelegateForMessageBodyType:(MessageBodyType)messageBodyType;

/**
 *  附件进度有更新
 */
- (void)messageViewController:(EaseMessageViewController *)viewController
               updateProgress:(float)progress
                 messageModel:(id<IMessageModel>)messageModel
                  messageBody:(id<IEMMessageBody>)messageBody;

/**
 *  消息时间间隔描述
 */
- (NSString *)messageViewController:(EaseMessageViewController *)viewController
                      stringForDate:(NSDate *)date;

/**
 *  获取消息，返回EMMessage类型的数据列表
 */
- (NSArray *)messageViewController:(EaseMessageViewController *)viewController
          loadMessageFromTimestamp:(long long)timestamp
                             count:(NSInteger)count;

/*!
 @method
 @brief 将EMMessage类型转换为符合<IMessageModel>协议的类型
 @discussion 将EMMessage类型转换为符合<IMessageModel>协议的类型,设置用户信息,消息显示用户昵称和头像
 @param viewController 当前消息视图
 @param EMMessage 聊天消息对象类型
 @result 返回<IMessageModel>协议的类型
 */
- (id<IMessageModel>)messageViewController:(EaseMessageViewController *)viewController
                           modelForMessage:(EMMessage *)message;

/*!
 @method
 @brief 是否允许长按
 @discussion 获取是否允许长按的回调,默认是NO
 @param viewController 当前消息视图
 @param indexPath 长按消息对应的indexPath
 @result
 */
- (BOOL)messageViewController:(EaseMessageViewController *)viewController
   canLongPressRowAtIndexPath:(NSIndexPath *)indexPath;

/*!
 @method
 @brief 触发长按手势
 @discussion 获取触发长按手势的回调,默认是NO
 @param viewController 当前消息视图
 @param indexPath 长按消息对应的indexPath
 @result
 */
- (BOOL)messageViewController:(EaseMessageViewController *)viewController
   didLongPressRowAtIndexPath:(NSIndexPath *)indexPath;

/**
 *  是否标记为已读
 *  message 指定的message
 */
- (BOOL)messageViewControllerShouldMarkMessagesAsRead:(EaseMessageViewController *)viewController;

/**
 *  是否发送已读回执
 *  message 要发送已读回执的message
 *  read    message是否已读
 */
- (BOOL)messageViewController:(EaseMessageViewController *)viewController
shouldSendHasReadAckForMessage:(EMMessage *)message
                         read:(BOOL)read;

/**
 * 判断消息是否为表情消息
 */
- (BOOL)isEmotionMessageFormessageViewController:(EaseMessageViewController *)viewController
                                    messageModel:(id<IMessageModel>)messageModel;

/**
 * 判断消息是否为表情消息
 */
- (EaseEmotion*)emotionURLFormessageViewController:(EaseMessageViewController *)viewController
                                   messageModel:(id<IMessageModel>)messageModel;

/**
 * 获取表情
 */
- (NSArray*)emotionFormessageViewController:(EaseMessageViewController *)viewController;

/**
 * 获取发送表情消息的扩展字段
 */
- (NSDictionary*)emotionExtFormessageViewController:(EaseMessageViewController *)viewController
                                        easeEmotion:(EaseEmotion*)easeEmotion;

@end

@interface EaseMessageViewController : EaseRefreshTableViewController<UINavigationControllerDelegate, UIImagePickerControllerDelegate, IChatManagerDelegate, IEMChatProgressDelegate, EMCallManagerCallDelegate, EMCDDeviceManagerDelegate, EMChatToolbarDelegate, EaseChatBarMoreViewDelegate, EMLocationViewDelegate>

@property (weak, nonatomic) id<EaseMessageViewControllerDelegate> delegate;

@property (weak, nonatomic) id<EaseMessageViewControllerDataSource> dataSource;

@property (strong, nonatomic) EMConversation *conversation;

@property (nonatomic) NSTimeInterval messageTimeIntervalTag;

//如果conversation中没有任何消息，退出该页面时是否删除该conversation
@property (nonatomic) BOOL deleteConversationIfNull; //default YES;

//当前页面显示时，是否滚动到最后一条
@property (nonatomic) BOOL scrollToBottomWhenAppear; //default YES;

//页面是否处于显示状态
@property (nonatomic) BOOL isViewDidAppear;

//加载的每页message的条数
@property (nonatomic) NSInteger messageCountOfPage; //default 50

//时间分割cell的高度
@property (nonatomic) CGFloat timeCellHeight;

//显示的EMMessage类型的消息列表
@property (strong, nonatomic) NSMutableArray *messsagesSource;

@property (strong, nonatomic) UIView *chatToolbar;

@property(strong, nonatomic) EaseChatBarMoreView *chatBarMoreView;

@property(strong, nonatomic) EaseFaceView *faceView;

@property(strong, nonatomic) EaseRecordView *recordView;

@property (strong, nonatomic) UIMenuController *menuController;

@property (strong, nonatomic) NSIndexPath *menuIndexPath;

@property (strong, nonatomic) UIImagePickerController *imagePicker;

- (instancetype)initWithConversationChatter:(NSString *)conversationChatter
                           conversationType:(EMConversationType)conversationType;

/**
 *  下拉加载更多
 */
- (void)tableViewDidTriggerHeaderRefresh;

/**
 *  发送文本消息
 */
- (void)sendTextMessage:(NSString *)text;

/**
 *  发送图片消息
 */
- (void)sendImageMessage:(UIImage *)image;

/**
 *  发送位置消息
 */
- (void)sendLocationMessageLatitude:(double)latitude
                          longitude:(double)longitude
                         andAddress:(NSString *)address;

/**
 *  发送语音消息
 */
- (void)sendVoiceMessageWithLocalPath:(NSString *)localPath
                             duration:(NSInteger)duration;

/**
 *  发送视频消息
 */
- (void)sendVideoMessageWithURL:(NSURL *)url;

/*
 *  添加消息
 */
-(void)addMessageToDataSource:(EMMessage *)message
                     progress:(id<IEMChatProgressDelegate>)progress;

@end
