// Author : Kgho	Github : https://github.com/kgho

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KBEGameMode.generated.h"

class UKBEventData;

/**
*
*/
UCLASS()
class RAINBOWSEVEN_C_API AKBEGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AKBEGameMode();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;

	//��������,���ߺ����ݶ����loginappת�Ƶ�baseapp
	void StartReloginBaseapp();

	void StopReloginBaseapp();

	//�󶨸���ʱ�����¼�
	void OnReloginBaseappTimer();

public:
protected:
	virtual void BeginPlay()override;

	//ע��KBE�¼�
	virtual void InstallEvent();

	//ע��KBE�¼�
	virtual void UnInstallEvent();

	virtual void OnKicked(const UKBEventData* EventData);

	virtual void OnDisconnected(const UKBEventData* EventData);

	virtual void OnConnectionState(const UKBEventData* EventData);

	virtual void OnReloginBaseappSuccessfully(const UKBEventData* EventData);

	virtual void OnReloginBaseappFailed(const UKBEventData* EventData);

protected:
	//������������ʱ��
	FTimerHandle  ReloginHandle;
};
