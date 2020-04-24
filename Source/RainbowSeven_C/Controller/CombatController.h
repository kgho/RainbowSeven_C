// Author : Kgho	Github : https://github.com/kgho

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CombatController.generated.h"

/**
 * 用于切换UI和Game游戏模式
 */
UCLASS()
class RAINBOWSEVEN_C_API ACombatController : public APlayerController
{
	GENERATED_BODY()

public:

	//切换输入模式
	void SwitchInputMode(bool IsShowUI);
	
};
