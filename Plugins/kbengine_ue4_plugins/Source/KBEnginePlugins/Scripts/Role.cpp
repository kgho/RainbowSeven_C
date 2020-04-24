#include "Role.h"
#include "Engine/KBEngine.h"
#include "Engine/KBEvent.h"
#include "ExCommon.h"
#include "Scripts/RSEventData.h"

KBEngine::Role::Role()
{
}

KBEngine::Role::~Role()
{
}

void KBEngine::Role::__init__()
{
	// ������Ҳ���Ҫ�������ͬ������
		// ����Ǳ������
	if (isPlayer())
	{
		//ע�ᶯ��ͬ���¼�
		KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("AnimUpdate", "AnimUpdate", [this](const UKBEventData* EventData)
			{
				const UKBEventData_AnimUpdate* ServerData = Cast<UKBEventData_AnimUpdate>(EventData);
				ANIM_INFO AnimInfo;
				AnimInfo.Speed = ServerData->Speed;
				AnimInfo.Direction = ServerData->Direction;
				pCellEntityCall->AnimUpdate(AnimInfo);
			});
	}

	DDH::Debug() << "Role::Init --> id: " << id() << DDH::Endl();
	DDH::Debug() << "Role::Init :--className_: >" << className_ << DDH::Endl();
}

void KBEngine::Role::onDestroy()
{
	//ע���ö���ע��������¼�
	KBENGINE_DEREGISTER_ALL_EVENT();
}

void KBEngine::Role::OnAnimUpdate(const ANIM_INFO& arg1)
{
	UKBEventData_OnAnimUpdate* EventData = NewObject<UKBEventData_OnAnimUpdate>();

	EventData->EntityId = id();
	EventData->Speed = arg1.Speed;
	EventData->Direction = arg1.Direction;

	KBENGINE_EVENT_FIRE("OnAnimUpdate", EventData);
}
