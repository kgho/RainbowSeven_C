// Author : Kgho	Github : https://github.com/kgho

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

class UTextBlock;
/**
 *
 */
UCLASS()
class RAINBOWSEVEN_C_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void OnReqAccountInfo(uint16 level, uint64 exp, uint64 fame, uint64 coin);

public:
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* Text_Level;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* Text_Exp_Current;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* Text_Fame;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* Text_Coin;
};
