// Author : Kgho	Github : https://github.com/kgho


#include "LoginGameMode.h"
#include "Engine/KBEngine.h"
#include "Scripts/ExCommon.h"
#include "Engine/KBEvent.h"
#include "Engine/KBEMain.h"
#include "UI/LoginWidget.h"
#include "KBEClient.h"

void ALoginGameMode::InstallEvent()
{
	Super::InstallEvent();

	//�����û����ʵ��ص�
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onCreateAccountResult, OnCreateAccountResult);
	//��½ʧ�ܻص�
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLoginFailed, OnLoginFailed);
	//�汾ƥ��ص�
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onVersionNotMatch, OnVersionNotMatch);
	//�汾��ƥ��ص�
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onScriptVersionNotMatch, OnScriptVersionNotMatch);
	//��½baseappʧ�ܻص�
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLoginBaseappFailed, OnLoginBaseappFailed);
	//��½baseapp�ص�
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLoginBaseapp, OnLoginBaseapp);
	//��½�ɹ��ص�, ���� Account���� __init__()ʱ����, ��������ת��ѡ���ɫ����
	KBENGINE_REGISTER_EVENT("onLoginSuccessfully", OnLoginSuccessfully);
}

void ALoginGameMode::BeginPlay()
{
	//ÿ�ν��뵽��¼����ǰ������һ��KBE,����KBE�����������һֱ����
	KBEngine::KBEngineApp::getSingleton().reset();
	Super::BeginPlay();
	//����UI
	LoginWidget = CreateWidget<ULoginWidget>(GetWorld(), LoginWidgetClass);
	LoginWidget->AddToViewport();
	LoginWidget->LoginGameMode = this;
	LoginWidget->InitWidget();
	//���������е����壬�ҵ�KBEMain
	for (TActorIterator<AKBEClient> ActorIt(GetWorld()); ActorIt; ++ActorIt)
	{
		KBEMain = (*ActorIt)->KBEMain;
	}
}

void ALoginGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	//ע���ö���ע��������¼�
	KBENGINE_DEREGISTER_ALL_EVENT();
}

void ALoginGameMode::OnCreateAccountResult(const UKBEventData* pEventData)
{
	//ת��Ϊ��Ӧ�Ĳ����ṹ�壬Ȼ���ӡ��Ϣ
	const UKBEventData_onCreateAccountResult* ServerData = Cast<UKBEventData_onCreateAccountResult>(pEventData);
	DDH::Debug() << "OnCreateAccountResult : errorCode-->" << ServerData->errorCode << "; errorstr -->" << ServerData->errorStr << DDH::Endl();
}

void ALoginGameMode::OnLoginFailed(const UKBEventData* pEventData)
{
	const UKBEventData_onLoginFailed* ServerData = Cast<UKBEventData_onLoginFailed>(pEventData);
	DDH::Debug() << "OnLoginFailed : failedcode-->" << ServerData->failedcode << "; errorstr -->" << ServerData->errorStr << DDH::Endl();
}

void ALoginGameMode::OnVersionNotMatch(const UKBEventData* pEventData)
{
	const UKBEventData_onVersionNotMatch* ServerData = Cast<UKBEventData_onVersionNotMatch>(pEventData);
	DDH::Debug() << "OnVersionNotMatch : serverVersion-->" << ServerData->serverVersion << "; clientVersion -->" << ServerData->clientVersion << DDH::Endl();
}

void ALoginGameMode::OnScriptVersionNotMatch(const UKBEventData* pEventData)
{
	const UKBEventData_onScriptVersionNotMatch* ServerData = Cast<UKBEventData_onScriptVersionNotMatch>(pEventData);
	DDH::Debug() << "OnScriptVersionNotMatch : clientScriptVersion-->" << ServerData->clientScriptVersion << "; serverScriptVersion -->" << ServerData->serverScriptVersion << DDH::Endl();
}

void ALoginGameMode::OnLoginBaseappFailed(const UKBEventData* pEventData)
{
	const UKBEventData_onLoginBaseappFailed* ServerData = Cast<UKBEventData_onLoginBaseappFailed>(pEventData);
	DDH::Debug() << "OnLoginBaseappFailed : failedcode-->" << ServerData->failedcode << "; errorStr -->" << ServerData->errorStr << DDH::Endl();
}

void ALoginGameMode::OnLoginBaseapp(const UKBEventData* pEventData)
{
	const UKBEventData_onLoginBaseapp* ServerData = Cast<UKBEventData_onLoginBaseapp>(pEventData);
	DDH::Debug() << "OnLoginBaseapp : eventName-->" << ServerData->eventName << DDH::Endl();
}

void ALoginGameMode::OnLoginSuccessfully(const UKBEventData* pEventData)
{
	const UKBEventData_onLoginSuccessfully* ServerData = Cast<UKBEventData_onLoginSuccessfully>(pEventData);
	DDH::Debug() << "OnLoginSuccessfully : entity_uuid-->" << ServerData->entity_uuid
		<< "; entity_id -->" << ServerData->entity_id
		<< "; eventName -->" << ServerData->eventName
		<< DDH::Endl();
	//��¼�ɹ�����ת���˵��������ڸó������Խ�����Ա��������ս���鿴���ϣ����õ�
	UGameplayStatics::OpenLevel(GetWorld(), FName("MenuMap"));
}

