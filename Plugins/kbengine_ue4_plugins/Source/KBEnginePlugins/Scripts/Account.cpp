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

//登录成功就会创建Account，然后执行该函数
void KBEngine::Account::__init__()
{
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