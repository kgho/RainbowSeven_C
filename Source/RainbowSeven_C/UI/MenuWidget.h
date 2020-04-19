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
class UScrollBox;
class URoomItem;
class UEditableTextBox;
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

	void ReqRoomList();

	UFUNCTION(BlueprintCallable)
		void CanvasRoleInfoHide();

	UFUNCTION(BlueprintCallable)
		void UnlockRoleSure();

	UFUNCTION(BlueprintCallable)
		void CanvasRoleUnlockBack();

	UFUNCTION(BlueprintCallable)
		void RoleUnlockSuccessfulBack();

	//Room
	UFUNCTION(BlueprintCallable)
		void ButtonCombatEvent();

	void OnReqRoomList(TArray<FROOM_INFO> RoomList);

	void OnCreateRoom(FROOM_INFO RoomInfo);


	UFUNCTION(BlueprintCallable)
		void CreateRoomEvent();

	UFUNCTION(BlueprintCallable)
		void EnterRoomEvent();

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

	//Room
	UPROPERTY(Meta = (BindWidget))
		UButton* Button_Combat;

	UPROPERTY(Meta = (BindWidget))
		UCanvasPanel* CanvasRoomMenu;

	UPROPERTY(Meta = (BindWidget))
		UScrollBox* Scroll_Box_RoomList;

	UPROPERTY(Meta = (BindWidget))
		UEditableTextBox* EditableTextBox_RoomName;

	UPROPERTY(EditAnywhere)
		TSubclassOf<URoomItem> RoomItemClass;

	UPROPERTY()
		TArray<URoomItem*> RoomItemGroup;

protected:

	void RoleItemSelect(uint8 RoleType, bool IsUnlock);

};
