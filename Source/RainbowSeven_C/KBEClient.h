// Author : Kgho	Github : https://github.com/kgho

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KBEClient.generated.h"

class UKBEMain;

UCLASS()
class RAINBOWSEVEN_C_API AKBEClient : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AKBEClient();

public:
	//KBEMain×é¼þ
	UPROPERTY(EditAnywhere)
		UKBEMain* KBEMain;
};