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

//��¼�ɹ��ͻᴴ��Account��Ȼ��ִ�иú���
void KBEngine::Account::__init__()
{
	//�û�ʵ�崴��˵����¼�ɹ���������¼�ɹ��¼�
	UKBEventData_onLoginSuccessfully* EventData = NewObject<UKBEventData_onLoginSuccessfully>();
	EventData->entity_uuid = KBEngineApp::getSingleton().entity_uuid();
	EventData->entity_id = id();
	KBENGINE_EVENT_FIRE("onLoginSuccessfully", EventData);

	// �����������˻���Ϣ
	pBaseEntityCall->ReqAccountInfo();

	// �����������Ա��Ϣ�б�
	pBaseEntityCall->ReqRoleList();
}

void KBEngine::Account::onDestroy()
{
	//ע���ö���ע��������¼�
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

//�����Ա��Ϣ�Ļص�����
void KBEngine::Account::OnReqRoleList(const ROLE_LIST& arg1)
{
	UKBEventData_OnReqRoleList* EventData = NewObject<UKBEventData_OnReqRoleList>();
	DDH::Debug() << "ExAccount::OnReqRoleList--> RoleList Number:" << arg1.Value.Num() << DDH::Endl();

	for (int i = 0; i < arg1.Value.Num(); i++)
	{
		//�����Ա�б���Ϣ���ص�����������
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
