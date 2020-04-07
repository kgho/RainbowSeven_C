// Author : Kgho	Github : https://github.com/kgho


#include "KBEGameMode.h"
#include "Engine/KBEngine.h"
#include "Scripts//ExCommon.h"
#include "Engine/World.h"
#include "Engine/Public/TimerManager.h"

AKBEGameMode::AKBEGameMode()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AKBEGameMode::BeginPlay()
{
	Super::BeginPlay();
	InstallEvent();
}

void AKBEGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UnInstallEvent();
}

void AKBEGameMode::StartReloginBaseapp()
{
	//�ж϶�ʱ������Ƿ����
	if (!ReloginHandle.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(ReloginHandle, this, &AKBEGameMode::OnReloginBaseappTimer, 1.f, true, 1.f);
	}
}

void AKBEGameMode::StopReloginBaseapp()
{
	//���þ������ʱ��
	if (!ReloginHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(ReloginHandle);
	}
}

void AKBEGameMode::OnReloginBaseappTimer()
{
	//���������¼���֪ͨ���������ж�������
	KBEngine::KBEngineApp::getSingleton().reloginBaseapp();
}

void AKBEGameMode::InstallEvent()
{
	//ע������Ļص��¼���KBEventTypes.cpp ������غ�logon��ص��¼�
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onKicked, OnKicked);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onDisconnected, OnDisconnected);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onConnectionState, OnConnectionState);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onReloginBaseappSuccessfully, OnReloginBaseappSuccessfully);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onReloginBaseappFailed, OnReloginBaseappFailed);
}

void AKBEGameMode::UnInstallEvent()
{
	KBENGINE_DEREGISTER_ALL_EVENT();
}

void AKBEGameMode::OnKicked(const UKBEventData* EventData)
{
	const UKBEventData_onKicked* ServerData = Cast<UKBEventData_onKicked>(EventData);
	DDH::Debug() << "OnKicked : failcode-->" << ServerData->failedcode << "; errorstr -->" << ServerData->errorStr << DDH::Endl();
}

void AKBEGameMode::OnDisconnected(const UKBEventData* EventData)
{
	const UKBEventData_onDisconnected* ServerData = Cast<UKBEventData_onDisconnected>(EventData);
	DDH::Debug() << "OnDisconnected : eventName-->" << ServerData->eventName << DDH::Endl();
}

void AKBEGameMode::OnConnectionState(const UKBEventData* EventData)
{
	const UKBEventData_onConnectionState* ServerData = Cast<UKBEventData_onConnectionState>(EventData);
	DDH::Debug() << "OnConnectionState : success-->" << ServerData->success << "; address -->" << ServerData->address << DDH::Endl();
}

void AKBEGameMode::OnReloginBaseappSuccessfully(const UKBEventData* EventData)
{
	const UKBEventData_onReloginBaseappSuccessfully* ServerData = Cast<UKBEventData_onReloginBaseappSuccessfully>(EventData);
	DDH::Debug() << "OnReloginBaseappSuccessfully : eventName-->" << ServerData->eventName << DDH::Endl();

	//�����ɹ���ֹͣ��ʱ��
	StopReloginBaseapp();
}

void AKBEGameMode::OnReloginBaseappFailed(const UKBEventData* EventData)
{
	const UKBEventData_onReloginBaseappFailed* ServerData = Cast<UKBEventData_onReloginBaseappFailed>(EventData);
	DDH::Debug() << "OnReloginBaseappFailed : failcode-->" << ServerData->failedcode << "; errorstr -->" << ServerData->errorStr << DDH::Endl();
}
