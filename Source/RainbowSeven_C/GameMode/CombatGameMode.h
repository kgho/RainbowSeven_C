// Author : Kgho	Github : https://github.com/kgho

#pragma once

#include "CoreMinimal.h"
#include "GameMode/KBEGameMode.h"
#include "CombatGameMode.generated.h"

/**
 * 绑定实体进入退出场景与移动等回调事件
 */

class APlayerCharacter;
class ARemoteCharacter;
class ACharacterEntity;

UCLASS()
class RAINBOWSEVEN_C_API ACombatGameMode : public AKBEGameMode
{
	GENERATED_BODY()

public:

	UPROPERTY()
		APlayerCharacter* PlayerCharacter;

	// 本地玩家类
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<APlayerCharacter>> PlayerClassList;

	// 远程玩家类
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<ARemoteCharacter>> RemoteClassList;

	// 字典保存了所有的非玩家实体，key：实体ID,value：干员角色指针
	TMap<int32, ACharacterEntity*> CharacterMap;


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
