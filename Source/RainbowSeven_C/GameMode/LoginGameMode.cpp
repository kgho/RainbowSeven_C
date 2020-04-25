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

	//创建用户入口实体回调
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onCreateAccountResult, OnCreateAccountResult);
	//登陆失败回调
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLoginFailed, OnLoginFailed);
	//版本匹配回调
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onVersionNotMatch, OnVersionNotMatch);
	//版本不匹配回调
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onScriptVersionNotMatch, OnScriptVersionNotMatch);
	//登陆baseapp失败回调
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLoginBaseappFailed, OnLoginBaseappFailed);
	//登陆baseapp回调
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLoginBaseapp, OnLoginBaseapp);
	//登陆成功回调, 生成 Account后在 __init__()时调用, 在这里跳转到选择角色场景
	KBENGINE_REGISTER_EVENT("onLoginSuccessfully", OnLoginSuccessfully);
}

void ALoginGameMode::BeginPlay()
{
	//每次进入到登录界面前先清理一次KBE,否则KBE插件缓存内容一直存在
	KBEngine::KBEngineApp::getSingleton().reset();
	Super::BeginPlay();
	//创建UI
	LoginWidget = CreateWidget<ULoginWidget>(GetWorld(), LoginWidgetClass);
	LoginWidget->AddToViewport();
	LoginWidget->LoginGameMode = this;
	LoginWidget->InitWidget();
	//遍历场景中的物体，找到KBEMain
	for (TActorIterator<AKBEClient> ActorIt(GetWorld()); ActorIt; ++ActorIt)
	{
		KBEMain = (*ActorIt)->KBEMain;
	}
}

void ALoginGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	//注销该对象注册的所有事件
	KBENGINE_DEREGISTER_ALL_EVENT();
}

void ALoginGameMode::OnCreateAccountResult(const UKBEventData* pEventData)
{
	//转换为相应的参数结构体，然后打印信息
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
	LoginWidget->ShowErrorPanel();
}

void ALoginGameMode::OnScriptVersionNotMatch(const UKBEventData* pEventData)
{
	const UKBEventData_onScriptVersionNotMatch* ServerData = Cast<UKBEventData_onScriptVersionNotMatch>(pEventData);
	DDH::Debug() << "OnScriptVersionNotMatch : clientScriptVersion-->" << ServerData->clientScriptVersion << "; serverScriptVersion -->" << ServerData->serverScriptVersion << DDH::Endl();
	LoginWidget->ShowErrorPanel();
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
	//登录成功后跳转到菜单场景，在该场景可以解锁干员，创建对战，查看资料，设置等
	UGameplayStatics::OpenLevel(GetWorld(), FName("MenuMap"));
}

