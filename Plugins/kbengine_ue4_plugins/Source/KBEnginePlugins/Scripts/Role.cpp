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
	// 本地玩家才需要向服务器同步数据
		// 如果是本地玩家
	if (isPlayer())
	{
		//注册动作同步事件
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
	//注销该对象注册的所有事件
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
