// Author : Kgho	Github : https://github.com/kgho

#pragma once

#include "CoreMinimal.h"
#include "GameMode/KBEGameMode.h"
#include "CombatGameMode.generated.h"

/**
 * 绑定实体进入退出场景与移动等回调事件
 */

class APlayerCharacter;

UCLASS()
class RAINBOWSEVEN_C_API ACombatGameMode : public AKBEGameMode
{
	GENERATED_BODY()

public:

	UPROPERTY()
		APlayerCharacter* PlayerCharacter;

	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<APlayerCharacter>> PlayerClassList;


public:
	virtual void UnInstallEvent() override;

protected:
	virtual void InstallEvent() override;

	virtual void BeginPlay() override;


	void OnEnterWorld(const UKBEventData* EventData);

	void OnEnterSpace(const UKBEventData* EventData);

	void OnLeaveWorld(const UKBEventData* EventData);

	void OnLeaveSpace(const UKBEventData* EventData);

	void SetPosition(const UKBEventData* EventData);

	void SetDirection(const UKBEventData* EventData);

	void UpdatePosition(const UKBEventData* EventData);

	void OnAnimUpdate(const UKBEventData* EventData);

	void SetBaseHP(const UKBEventData* EventData);

	void SetHP(const UKBEventData* EventData);

};
