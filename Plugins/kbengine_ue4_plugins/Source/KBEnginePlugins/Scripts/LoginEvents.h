#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/KBEvent.h"
#include "Engine/KBECommon.h"
#include "LoginEvents.generated.h"

UCLASS()
class KBENGINEPLUGINS_API ULoginEvents : public UObject
{
	GENERATED_BODY()
};

//方法对应的参数结构体
UCLASS(BlueprintType, Blueprintable)
class KBENGINEPLUGINS_API UKBEventData_OnSay :public  UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
		FString Name;
	UPROPERTY(BlueprintReadOnly)
		FString Time;
	UPROPERTY(BlueprintReadOnly)
		FString Msg;
};
UCLASS(BlueprintType, Blueprintable)
class KBENGINEPLUGINS_API UKBEventData_Say :public  UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
		FString Msg;
};