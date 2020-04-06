#include "Account.h"
#include "Engine/KBEngine.h"
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
	if (isPlayer())
	{
		//�ٷ�ע���¼�
		KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("Say", "Say", [this](const  UKBEventData* EventData)
			{
				const UKBEventData_Say* ValueData = Cast<UKBEventData_Say>(EventData);
				pCellEntityCall->Say(ValueData->Msg);//��������������ˣ�Account.py��Say����������˵��ñ��ͻ��˵�OnSay���й㲥
			}
		);
		UKBEventData* EventData = NewObject<UKBEventData>(); //UKBEventData�ƺ���Ĭ�ϵģ�UKBEventData_OnSay�Լ�������?
		KBENGINE_EVENT_FIRE("OnLoginSucced", EventData); //������Ϸ��¼�ɹ�
	}
}
void KBEngine::Account::onDestroy()
{

	KBENGINE_EVENT_FIRE("QuitGame", NewObject< UKBEventData>());
	//ע���ö���ע��������¼�
	KBENGINE_DEREGISTER_ALL_EVENT();
}

void KBEngine::Account::OnSay(const CHAT_INFO& arg1)
{
	UKBEventData_OnSay* EventData = NewObject<UKBEventData_OnSay>();
	EventData->Name = arg1.Name;
	EventData->Time = arg1.Time;
	EventData->Msg = arg1.Msg;
	KBENGINE_EVENT_FIRE("OnSay", EventData);//��EventData����OnSay
}