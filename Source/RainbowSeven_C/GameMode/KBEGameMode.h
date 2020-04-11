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

	//断线重连,断线后数据都会从loginapp转移到baseapp
	void StartReloginBaseapp();

	void StopReloginBaseapp();

	//绑定给定时器的事件
	void OnReloginBaseappTimer();

public:
protected:
	virtual void BeginPlay()override;

	//注册KBE事件
	virtual void InstallEvent();

	//注销KBE事件
	virtual void UnInstallEvent();

	virtual void OnKicked(const UKBEventData* EventData);

	virtual void OnDisconnected(const UKBEventData* EventData);

	virtual void OnConnectionState(const UKBEventData* EventData);

	virtual void OnReloginBaseappSuccessfully(const UKBEventData* EventData);

	virtual void OnReloginBaseappFailed(const UKBEventData* EventData);

protected:
	//断线重连，定时器
	FTimerHandle  ReloginHandle;
};
