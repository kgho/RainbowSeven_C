// Author : Kgho	Github : https://github.com/kgho

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SlateTypes.h"
#include "RoleItem.generated.h"

class UTextBlock;
class UButton;

DECLARE_DELEGATE_TwoParams(FRoleItemSelect, uint8, bool)
/**
 *
 */
UCLASS()
class RAINBOWSEVEN_C_API URoleItem : public UUserWidget
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

	UPROPERTY(EditAnywhere)
		uint16 Fame;

	UPROPERTY(EditAnywhere)
		uint16 Coin;

	UPROPERTY(Meta = (BindWidget))
		UButton* Button;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* Text_IsUnlock;

	UPROPERTY(EditAnywhere)
		FButtonStyle RoleStyle;

	FRoleItemSelect RoleItemSelectDel;
};
