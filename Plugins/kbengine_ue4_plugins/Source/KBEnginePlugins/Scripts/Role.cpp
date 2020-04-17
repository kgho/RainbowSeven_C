#include "Role.h"
#include "Engine/KBEngine.h"
#include "Engine/KBEvent.h"

KBEngine::Role::Role()
{
}

KBEngine::Role::~Role()
{
}

void KBEngine::Role::__init__()
{
}

void KBEngine::Role::onDestroy()
{
	//注销该对象注册的所有事件
	KBENGINE_DEREGISTER_ALL_EVENT();
}