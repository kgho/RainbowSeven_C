#include "Account.h"
#include "Engine/KBEngine.h"
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
	if (isPlayer())
	{
		//官方注册事件
		KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("Say", "Say", [this](const  UKBEventData* EventData)
			{
				const UKBEventData_Say* ValueData = Cast<UKBEventData_Say>(EventData);
				pCellEntityCall->Say(ValueData->Msg);//将参数传给服务端，Account.py的Say方法，服务端调用本客户端的OnSay进行广播
			}
		);
		UKBEventData* EventData = NewObject<UKBEventData>(); //UKBEventData似乎是默认的，UKBEventData_OnSay自己创建的?
		KBENGINE_EVENT_FIRE("OnLoginSucced", EventData); //告诉游戏登录成功
	}
}
void KBEngine::Account::onDestroy()
{

	KBENGINE_EVENT_FIRE("QuitGame", NewObject< UKBEventData>());
	//注销该对象注册的所有事件
	KBENGINE_DEREGISTER_ALL_EVENT();
}

void KBEngine::Account::OnSay(const CHAT_INFO& arg1)
{
	UKBEventData_OnSay* EventData = NewObject<UKBEventData_OnSay>();
	EventData->Name = arg1.Name;
	EventData->Time = arg1.Time;
	EventData->Msg = arg1.Msg;
	KBENGINE_EVENT_FIRE("OnSay", EventData);//将EventData传给OnSay
}