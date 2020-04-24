// Author : Kgho	Github : https://github.com/kgho

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CombatController.generated.h"

/**
 * �����л�UI��Game��Ϸģʽ
 */
UCLASS()
class RAINBOWSEVEN_C_API ACombatController : public APlayerController
{
	GENERATED_BODY()

public:

	//�л�����ģʽ
	void SwitchInputMode(bool IsShowUI);
	
};
