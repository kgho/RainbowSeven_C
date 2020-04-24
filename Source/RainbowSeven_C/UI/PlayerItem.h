// Author : Kgho	Github : https://github.com/kgho

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Scripts/RSEventData.h"
#include "PlayerItem.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class RAINBOWSEVEN_C_API UPlayerItem : public UUserWidget
{
	GENERATED_BODY()

public:
	void RefreshItem(FPLAYER_INFO InPlayerInfo);

public:
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* Text_Username;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* Text_State;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* Text_Level;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* Text_Master;
};
