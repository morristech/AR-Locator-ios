//
// XMPPRoom
// A chat room. XEP-0045 Implementation.
//

#import <Foundation/Foundation.h>

#import "QBXMPP.h"
#import "QBXMPPRoomOccupant.h"

#define requestRoomUsersQueryIDPrefix @"561003"

@interface QBXMPPRoom : QBXMPPModule
{
	NSString *roomName;
	NSString *nickName;
	NSString *subject;
	NSString *invitedUser;
	BOOL _isJoined;
	NSMutableDictionary *occupants;
    
    BOOL isMembersOnlyRoom;
    BOOL isPersistentRoom;
}

- (id)initWithRoomName:(NSString *)roomName nickName:(NSString *)nickName;
- (id)initWithRoomName:(NSString *)roomName nickName:(NSString *)nickName dispatchQueue:(dispatch_queue_t)queue;

@property (readonly) NSString *roomName;
@property (readonly) NSString *nickName;
@property (readonly) NSString *subject;

@property (readonly, assign) BOOL isJoined;

@property (readonly) NSDictionary *occupants;

@property (readwrite, copy) NSString *invitedUser;

@property (nonatomic, assign) BOOL isMembersOnlyRoom;
@property (nonatomic, assign) BOOL isPersistentRoom;

- (void)createOrJoinRoom;
- (void)joinRoom;
- (void)leaveRoom;

- (void)chageNickForRoom:(NSString *)name;

- (void)inviteUser:(QBXMPPJID *)jid withMessage:(NSString *)invitationMessage;
- (void)acceptInvitation;
- (void)rejectInvitation;
- (void)rejectInvitationWithMessage:(NSString *)reasonForRejection;

- (void)requestUsers;

- (void)sendMessage:(NSString *)msg;

+ (NSDictionary *)Errors;

@end

@protocol QBXMPPRoomDelegate <NSObject>
@optional

- (void)xmppRoomDidCreate:(QBXMPPRoom *)sender;
- (void)xmppRoomDidEnter:(QBXMPPRoom *)sender;
- (void)xmppRoomDidNotEnter:(QBXMPPRoom *)sender error:(NSError *)error;
- (void)xmppRoomDidLeave:(QBXMPPRoom *)sender;
- (void)xmppRoom:(QBXMPPRoom *)sender didReceiveMessage:(QBXMPPMessage *)message fromNick:(NSString *)nick;
- (void)xmppRoom:(QBXMPPRoom *)sender didChangeOccupants:(NSDictionary *)occupants;

@end
