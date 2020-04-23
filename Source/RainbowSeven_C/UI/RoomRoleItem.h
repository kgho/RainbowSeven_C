// Author : Kgho	Github : https://github.com/kgho

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SlateTypes.h"
#include "RoomRoleItem.generated.h"

class UTextBlock;
class UButton;

//DECLARE_DELEGATE_TwoParams(FItemSelect, uint8, bool)
/**
 * 在房间中选择角色的 item
 */
UCLASS()
class RAINBOWSEVEN_C_API URoomRoleItem : public UUserWidget
{
	GENERATED_BODY()

public:
	void RefreshItem(uint8 RoleID, uint8 isLock);

	UFUNCTION(BlueprintCallable)
		void InitItemStyle();

	UFUNCTION(BlueprintCallable)
		void ButtonReleasedEvent();

public:
	UPROPERTY(EditAnywhere)
		uint8 RoleType;

	UPROPERTY(BlueprintReadWrite)
		bool isUnlock;

	UPROPERTY(Meta = (BindWidget))
		UButton* Button;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* Text_IsUnlock;

	UPROPERTY(EditAnywhere)
		FButtonStyle ButtonStyle;

	//FItemSelect ItemSelectDel;
};
