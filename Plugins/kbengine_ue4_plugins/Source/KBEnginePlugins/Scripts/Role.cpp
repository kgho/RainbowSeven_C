#include "Role.h"
#include "Engine/KBEngine.h"
#include "Engine/KBEvent.h"
#include "ExCommon.h"

KBEngine::Role::Role()
{
}

KBEngine::Role::~Role()
{
}

void KBEngine::Role::__init__()
{
	DDH::Debug() << "Role::Init --> id: " << id() << DDH::Endl();
	DDH::Debug() << "Role::Init :--className_: >" << className_ << DDH::Endl();
	DDH::Debug() << "Role::Init :--spaceID: >" << (int)spaceID << DDH::Endl();
	DDH::Debug() << "Role::Init :--isPlayer: >" << isPlayer() << DDH::Endl();
	DDH::Debug() << "Role::Init :--spaceID: >" << (int)spaceID << DDH::Endl();
}

void KBEngine::Role::onDestroy()
{
	//注销该对象注册的所有事件
	KBENGINE_DEREGISTER_ALL_EVENT();
}