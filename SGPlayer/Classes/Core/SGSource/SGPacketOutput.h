//
//  SGURLSource.h
//  SGPlayer
//
//  Created by Single on 2018/1/16.
//  Copyright © 2018年 single. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SGAsset.h"
#import "SGPacket.h"

@protocol SGPacketOutputDelegate;

typedef NS_ENUM(NSUInteger, SGPacketOutputState)
{
    SGPacketOutputStateNone,
    SGPacketOutputStateOpening,
    SGPacketOutputStateOpened,
    SGPacketOutputStateReading,
    SGPacketOutputStatePaused,
    SGPacketOutputStateSeeking,
    SGPacketOutputStateFinished,
    SGPacketOutputStateClosed,
    SGPacketOutputStateFailed,
};

@interface SGPacketOutput : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithAsset:(SGAsset *)asset;

@property (nonatomic, weak) id <SGPacketOutputDelegate> delegate;

- (SGPacketOutputState)state;
- (NSError *)error;
- (CMTime)duration;
- (NSDictionary *)metadata;
- (NSArray <SGStream *> *)streams;
- (NSArray <SGStream *> *)audioStreams;
- (NSArray <SGStream *> *)videoStreams;
- (NSArray <SGStream *> *)otherStreams;

- (NSError *)open;
- (NSError *)start;
- (NSError *)close;
- (NSError *)pause;
- (NSError *)resume;
- (NSError *)seekable;
- (NSError *)seekToTime:(CMTime)time completionHandler:(void(^)(CMTime time, NSError * error))completionHandler;

@end

@protocol SGPacketOutputDelegate <NSObject>

- (void)packetOutput:(SGPacketOutput *)packetOutput didChangeState:(SGPacketOutputState)state;
- (void)packetOutput:(SGPacketOutput *)packetOutput didOutputPacket:(SGPacket *)packet;

@end
