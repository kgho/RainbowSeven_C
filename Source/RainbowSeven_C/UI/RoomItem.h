// Author : Kgho	Github : https://github.com/kgho

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Scripts/RSEventData.h"
#include "RoomItem.generated.h"

class UImage;
class UTextBlock;

DECLARE_DELEGATE_OneParam(FItemSelect, uint64)
/**
 *
 */
UCLASS()
class RAINBOWSEVEN_C_API URoomItem : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		void ItemButtonEvent();

	void InitItem(FROOM_INFO InRoomInfo);

	void ItemSelect();

	void ItemUnSelect();



public:
	UPROPERTY(Meta = (BindWidget))
		UImage* Image_Outline;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* Text_Name;

	UPROPERTY()
		FROOM_INFO RoomInfo;

	FItemSelect ItemSelectDel;

	bool IsSelected;

};
