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
	//ע���ö���ע��������¼�
	KBENGINE_DEREGISTER_ALL_EVENT();
}