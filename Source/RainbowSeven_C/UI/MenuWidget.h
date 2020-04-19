// Author : Kgho	Github : https://github.com/kgho

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Scripts/RSEventData.h"
#include "SlateTypes.h"
#include "MenuWidget.generated.h"

class UTextBlock;
class UProgressBar;
class UButton;
class URoleItem;
class UCanvasPanel;
/**
 *
 */
UCLASS()
class RAINBOWSEVEN_C_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void OnReqAccountInfo(uint16 level, uint64 exp, uint64 fame, uint64 coin);

	void OnReqRoleList(TArray<FROLE_INFO> RoleList);

	void RefreshRoleInfo(FROLE_INFO RoleInfo);

	void OnReqUnlockRole(uint8 result);

	UFUNCTION(BlueprintCallable)
		void CanvasRoleInfoHide();

	UFUNCTION(BlueprintCallable)
		void UnlockRoleSure();

	UFUNCTION(BlueprintCallable)
		void CanvasRoleUnlockBack();

	UFUNCTION(BlueprintCallable)
		void RoleUnlockSuccessfulBack();

public:
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* Text_Level;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* Text_Exp_Current;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* Text_Exp_Total;

	UPROPERTY(Meta = (BindWidget))
		UProgressBar* ProgressBar_Exp;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* Text_Fame;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* Text_Coin;

	UPROPERTY(BlueprintReadWrite)
		TArray<URoleItem*> RoleItemArray;

	uint8 selectedRoleType;

	//Canvas Role Info
	UPROPERTY(Meta = (BindWidget))
		UCanvasPanel* CanvasRoleInfo;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* Text_Role_Info_Name;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* Text_KDA;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* Text_Role_Info_Kill;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* Text_Role_Info_Death;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* Text_Role_Info_Assist;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* Text_Role_Info_PlayCount;

	//Canvas Role Unlock
	UPROPERTY(Meta = (BindWidget))
		UCanvasPanel* CanvasRoleUnlock;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* Text_Role_Unlock_Name;

	UPROPERTY(Meta = (BindWidget))
		UCanvasPanel* CanvasRoleUnlockSuccessful;

	UPROPERTY(Meta = (BindWidget))
		UButton* Button_Role_Unlock_Successful_Back;

protected:

	void RoleItemSelect(uint8 RoleType, bool IsUnlock);

};
