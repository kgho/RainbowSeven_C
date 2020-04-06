// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Scripts/LoginEvents.h"
#include "LoginGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class RAINBOWSEVEN_C_API ALoginGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
		void Say(FString Msg);

	//实体销毁后注销事件，防止空指针
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;

protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintImplementableEvent)
		void OnSay(const UKBEventData* EventData);
	UFUNCTION(BlueprintImplementableEvent)
		void OnLoginSucced(const UKBEventData* EventData);
	UFUNCTION(BlueprintImplementableEvent)
		void AddSpaceGeometryMapping(const UKBEventData* EventData);
};
