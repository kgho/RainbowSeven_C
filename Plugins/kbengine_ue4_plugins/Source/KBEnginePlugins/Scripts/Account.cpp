#include "Account.h"
#include "Engine/KBEngine.h"
#include "Engine//KBEvent.h"
#include "LoginEvents.h"	

KBEngine::Account::Account() :AccountBase()
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
}

void KBEngine::Account::onDestroy()
{
	//ע���ö���ע��������¼�
	KBENGINE_DEREGISTER_ALL_EVENT();
}