#include "Gate.h"
#include "Engine/KBEngine.h"
#include "LoginEvents.h"	
KBEngine::Gate::Gate() :GateBase()
{
}
KBEngine::Gate::~Gate()
{
}
//��¼�ɹ��ͻᴴ��Gate��Ȼ��ִ�иú���
void KBEngine::Gate::__init__()
{
	
}
void KBEngine::Gate::onDestroy()
{
	//ע���ö���ע��������¼�
	KBENGINE_DEREGISTER_ALL_EVENT();
}