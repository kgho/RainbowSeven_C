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
	//用户实体创建说明登录成功，触发登录成功事件
	UKBEventData_onLoginSuccessfully* EventData = NewObject<UKBEventData_onLoginSuccessfully>();
	EventData->entity_uuid = KBEngineApp::getSingleton().entity_uuid();
	EventData->entity_id = id();
	KBENGINE_EVENT_FIRE("onLoginSuccessfully", EventData);

	// 向服务端请求账户信息
	pBaseEntityCall->ReqAccountInfo();

	// 向服务端请求干员信息列表
	pBaseEntityCall->ReqRoleList();
}

void KBEngine::Account::onDestroy()
{
	//注销该对象注册的所有事件
	KBENGINE_DEREGISTER_ALL_EVENT();
}

void KBEngine::Account::OnReqAccountInfo(uint16 arg1, uint64 arg2, uint64 arg3, uint64 arg4)
{
	UKBEventData_OnReqAccountInfo* EventData = NewObject<UKBEventData_OnReqAccountInfo>();
	DDH::Debug() << "ExAccount::OnReqAccountInfo--> Level = " << arg1 << ", Exp = " << arg2 << ", Fame = " << arg3 << ", Coin = " << arg4 << DDH::Endl();

	EventData->Level = arg1;
	EventData->Exp = arg2;
	EventData->Fame = arg3;
	EventData->Coin = arg4;

	KBENGINE_EVENT_FIRE("OnReqAccountInfo", EventData);
}

//请求干员信息的回调函数
void KBEngine::Account::OnReqRoleList(const ROLE_LIST& arg1)
{
	UKBEventData_OnReqRoleList* EventData = NewObject<UKBEventData_OnReqRoleList>();
	DDH::Debug() << "ExAccount::OnReqRoleList--> RoleList Number:" << arg1.Value.Num() << DDH::Endl();

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
	DDH::Debug() << "ExAccount::OnReqUnlockRole--> Result:" << arg1 << ", RoelType:" << arg2 << DDH::Endl();
}
