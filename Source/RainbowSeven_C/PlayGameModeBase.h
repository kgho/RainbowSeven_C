// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Scripts/LoginEvents.h"
#include "PlayGameModeBase.generated.h"
class ADefaultCharacter;
/**
*
*/
UCLASS()
class RAINBOWSEVEN_C_API APlayGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<ADefaultCharacter> PlayerCharacterClass;
	UPROPERTY(EditAnywhere)
		FVector PlayerSpawnPos;
	//用指针保存玩家生成的 Character
	ADefaultCharacter* PlayerCharacter;
protected:
	virtual void BeginPlay() override;
	void OnEnterWorld(const UKBEventData* EventData);
	void OnLeaveWorld(const UKBEventData* EventData);
	void OnEnterSpace(const UKBEventData* EventData);
	void OnLeaveSpace(const UKBEventData* EventData);
};
