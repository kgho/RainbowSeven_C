#include "Account.h"
#include "Engine/KBEngine.h"
#include "Engine/KBEvent.h"
#include "RSEventData.h"
#include "ExCommon.h"

KBEngine::Account::Account()
{
}

KBEngine::Account::~Account()
{
}

//登录成功就会创建Account，然后执行该函数
void KBEngine::Account::__init__()
{
	if (!isPlayer()) {
		DDH::Debug() << "Account::Init Other:-->" << id() << DDH::Endl();
		return;
	}

	DDH::Debug() << "Account::Init-->" << DDH::Endl();

	//向服务端请求账户信息
	pBaseEntityCall->ReqAccountInfo();

	//向服务端请求干员信息列表
	pBaseEntityCall->ReqRoleList();

	// 注册事件
	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqRoleInfo", "ReqRoleInfo", [this](const UKBEventData* EventData) {
		const UKBEventData_ReqRoleInfo* ServerData = Cast<UKBEventData_ReqRoleInfo>(EventData);

		pBaseEntityCall->ReqRoleInfo(ServerData->RoleType);
		});

	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqUnlockRole", "ReqUnlockRole", [this](const UKBEventData* EventData) {
		const UKBEventData_ReqUnlockRole* ServerData = Cast<UKBEventData_ReqUnlockRole>(EventData);

		pBaseEntityCall->ReqUnlockRole(ServerData->RoleType);
		});

	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqRoleList", "ReqRoleList", [this](const UKBEventData* EventData) {
		const UKBEventData_ReqRoleList* ServerData = Cast<UKBEventData_ReqRoleList>(EventData);

		pBaseEntityCall->ReqRoleList();
		});

	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqRoomList", "ReqRoomList", [this](const UKBEventData* EventData)
		{
			pBaseEntityCall->ReqRoomList();
		});

	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqCreateRoom", "ReqCreateRoom", [this](const UKBEventData* EventData)
		{

			const UKBEventData_ReqCreateRoom* ServerData = Cast<UKBEventData_ReqCreateRoom>(EventData);
			DDH::Debug() << "Account::ReqCreateRoom--> RoomName:= " << ServerData->RoomName << DDH::Endl();
			pBaseEntityCall->ReqCreateRoom(ServerData->RoomName);
		});

	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqEnterRoom", "ReqEnterRoom", [this](const UKBEventData* EventData)
		{
			const UKBEventData_ReqEnterRoom* ServerData = Cast<UKBEventData_ReqEnterRoom>(EventData);
			pBaseEntityCall->ReqEnterRoom(ServerData->RoomId);
		});

	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqLeaveRoom", "ReqLeaveRoom", [this](const UKBEventData* EventData)
		{
			pBaseEntityCall->ReqLeaveRoom();
		});

	//用户实体创建说明登录成功，触发登录成功事件
	UKBEventData_onLoginSuccessfully* EventData = NewObject<UKBEventData_onLoginSuccessfully>();
	EventData->entity_uuid = KBEngineApp::getSingleton().entity_uuid();
	EventData->entity_id = id();
	KBENGINE_EVENT_FIRE("onLoginSuccessfully", EventData);

}

void KBEngine::Account::onDestroy()
{
	//注销该对象注册的所有事件
	KBENGINE_DEREGISTER_ALL_EVENT();
}

void KBEngine::Account::OnReqAccountInfo(uint16 arg1, uint64 arg2, uint64 arg3, uint64 arg4)
{
	UKBEventData_OnReqAccountInfo* EventData = NewObject<UKBEventData_OnReqAccountInfo>();
	DDH::Debug() << "Account::OnReqAccountInfo--> Level = " << arg1 << ", Exp = " << arg2 << ", Fame = " << arg3 << ", Coin = " << arg4 << DDH::Endl();

	EventData->Level = arg1;
	EventData->Exp = arg2;
	EventData->Fame = arg3;
	EventData->Coin = arg4;

	KBENGINE_EVENT_FIRE("OnReqAccountInfo", EventData);
}

void KBEngine::Account::OnReqRoleInfo(const ROLE_INFO& arg1)
{
	UKBEventData_OnReqRoleInfo* EventData = NewObject<UKBEventData_OnReqRoleInfo>();
	FROLE_INFO RoleInfo;
	RoleInfo.InitData(arg1.Dbid, arg1.RoleType, arg1.IsLock, arg1.Kill, arg1.Death, arg1.Assist, arg1.Point, arg1.PlayCount);
	EventData->RoleInfo = RoleInfo;

	DDH::Debug() << "Account::OnReqRoleInfo--> Kill:" << uint64(arg1.Kill) << DDH::Endl();

	KBENGINE_EVENT_FIRE("OnReqRoleInfo", EventData);
}

//请求干员信息的回调函数
void KBEngine::Account::OnReqRoleList(const ROLE_LIST& arg1)
{
	UKBEventData_OnReqRoleList* EventData = NewObject<UKBEventData_OnReqRoleList>();
	DDH::Debug() << "Account::OnReqRoleList--> RoleList Number:" << arg1.Value.Num() << DDH::Endl();

	for (int i = 0; i < arg1.Value.Num(); i++)
	{
		//保存干员列表信息到回调方法参数类
		FROLE_INFO RoleInfo;
		RoleInfo.InitData(arg1.Value[i].Dbid, arg1.Value[i].RoleType, arg1.Value[i].IsLock, arg1.Value[i].Kill, arg1.Value[i].Death, arg1.Value[i].Assist, arg1.Value[i].Point, arg1.Value[i].PlayCount);
		EventData->RoleList.Add(RoleInfo);
	}
	KBENGINE_EVENT_FIRE("OnReqRoleList", EventData);
}

void KBEngine::Account::OnReqUnlockRole(uint8 arg1, uint8 arg2)
{
	UKBEventData_OnReqUnlockRole* EventData = NewObject< UKBEventData_OnReqUnlockRole>();
	EventData->Result = arg1;
	DDH::Debug() << "Account::OnReqUnlockRole--> Result:" << arg1 << ", RoelType:" << arg2 << DDH::Endl();
	KBENGINE_EVENT_FIRE("OnReqUnlockRole", EventData);
}

//房间

void KBEngine::Account::OnReqRoomList(const ROOM_LIST& arg1)
{
	UKBEventData_OnReqRoomList* EventData = NewObject<UKBEventData_OnReqRoomList>();
	for (int i = 0; i < arg1.Value.Num(); ++i)
	{
		FROOM_INFO RoomInfo;
		RoomInfo.InitData(arg1.Value[i].RoomId, arg1.Value[i].Name);
		EventData->RoomList.Add(RoomInfo);
	}

	KBENGINE_EVENT_FIRE("OnReqRoomList", EventData);
}
void KBEngine::Account::OnReqCreateRoom(uint8 arg1, const ROOM_INFO& arg2)
{
	if (arg1 == 1)
	{
		DDH::Debug() << "ExAccount::OnReqCreateRoom Failed By Name --> " << arg2.Name << DDH::Endl();
		return;
	}
	UKBEventData_OnReqCreateRoom* EventData = NewObject<UKBEventData_OnReqCreateRoom>();
	EventData->RoomInfo.InitData(arg2.RoomId, arg2.Name);

	KBENGINE_EVENT_FIRE("OnReqCreateRoom", EventData);
}

void KBEngine::Account::OnReqEnterRoom(uint8 arg1, const PLAYER_LIST& arg2, const PLAYER_LIST& arg3)
{
	DDH::Debug() << "Account::OnReqEnterRoom--> arg1:" << arg1 << DDH::Endl();
	switch (arg1)
	{

	case 0:
	{
		UKBEventData_OnReqEnterRoom* EventData = NewObject<UKBEventData_OnReqEnterRoom>();
		DDH::Debug() << "Account::OnReqEnterRoom--> PlayerBlue Number:" << arg2.Value.Num() << DDH::Endl();

		// 蓝队
		for (int i = 0; i < arg2.Value.Num(); i++)
		{
			FPLAYER_INFO PlayerInfo;
			PlayerInfo.InitData(arg2.Value[i].Name, arg2.Value[i].Level, arg2.Value[i].State, arg2.Value[i].Avatar, arg2.Value[i].Master);
			DDH::Debug() << "Account::OnReqEnterRoom--> Name:" << arg2.Value[i].Name << "IsMaster:" << arg2.Value[i].Master << DDH::Endl();
			EventData->PlayerListBlue.Add(PlayerInfo);
		}

		DDH::Debug() << "Account::OnReqEnterRoom--> PlayerRed Number:" << arg3.Value.Num() << DDH::Endl();
		// 红队
		for (int i = 0; i < arg3.Value.Num(); i++)
		{
			FPLAYER_INFO PlayerInfo;
			PlayerInfo.InitData(arg3.Value[i].Name, arg3.Value[i].Level, arg3.Value[i].State, arg3.Value[i].Avatar, arg3.Value[i].Master);
			DDH::Debug() << "Account::OnReqEnterRoom--> Name:" << arg3.Value[i].Name << "IsMaster:" << arg3.Value[i].Master << DDH::Endl();
			EventData->PlayerListRed.Add(PlayerInfo);
		}

		KBENGINE_EVENT_FIRE("OnReqEnterRoom", EventData);
	}
	break;

	case 1:
	{
		KBENGINE_EVENT_FIRE("OnReqEnterRoomFailed", NewObject<UKBEventData>());
	}
	break;

	case 2:
	{
		KBENGINE_EVENT_FIRE("OnReqEnterRoomFull", NewObject<UKBEventData>());
	}
	break;

	}
}

void  KBEngine::Account::OnReqLeaveRoom(uint8 arg1)
{
	DDH::Debug() << "Account::OnReqLeaveRoom--> arg1:" << arg1 << DDH::Endl();
	KBENGINE_EVENT_FIRE("OnReqLeaveRoom", NewObject<UKBEventData>());
}




