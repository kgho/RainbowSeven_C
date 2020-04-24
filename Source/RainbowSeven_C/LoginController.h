// Author : Kgho	Github : https://github.com/kgho

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LoginController.generated.h"

/**
*
*/
UCLASS()
class RAINBOWSEVEN_C_API ALoginController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		int32 ScreenWidth;

	UPROPERTY(EditAnywhere)
		int32 ScreenHeight;

protected:
	virtual void BeginPlay() override;
};
