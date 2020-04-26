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
class UPlayerItem;
class UVerticalBox;
class URoomRoleItem;
/**
 *
 */
UCLASS()
class RAINBOWSEVEN_C_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct();

	void OnReqAccountInfo(FString name, uint16 level, uint64 exp, uint64 fame, uint64 coin);

	void OnReqRoleList(TArray<FROLE_INFO> InRoleList);

	void RefreshRoleInfo(FROLE_INFO RoleInfo);

	void OnReqUnlockRole(uint8 result);

	void ReqRoomList();

	void OnReqEnterRoomFailed();

	void OnReqEnterRoomFull();

	void OnReqLeaveRoom();

	void ReqChangeState();

	//Main
	UFUNCTION(BlueprintCallable)
		void ButtonHomeEvent();

	UFUNCTION(BlueprintCallable)
		void ButtonRoleEvent();

	UFUNCTION(BlueprintCallable)
		void ButtonCombatEvent();

	UFUNCTION(BlueprintCallable)
		void ButtonRefreshRoomEvent();

	UFUNCTION(BlueprintCallable)
		void ButtonLeaveRoomEvent();

	//Role
	UFUNCTION(BlueprintCallable)
		void CanvasRoleInfoHide();

	UFUNCTION(BlueprintCallable)
		void UnlockRoleSure();

	UFUNCTION(BlueprintCallable)
		void CanvasRoleUnlockBack();

	UFUNCTION(BlueprintCallable)
		void RoleUnlockSuccessfulBack();

	//Room
	void OnReqRoomList(TArray<FROOM_INFO> RoomList);

	void OnReqCreateRoom(FROOM_INFO RoomInfo);

	void RoomItemSelect(uint64 RoomId);


	void OnReqEnterRoom(TArray<FPLAYER_INFO> PlayerListBlue, TArray<FPLAYER_INFO> PlayerListRed);

	void OnReqChangeState(uint8 state);

	void OnReqSelectRole(uint8 roleType);

	void OnAllReady(uint8 allReady);

	void ReqStartGame();

	void LoadGame();

	UFUNCTION(BlueprintCallable)
		void ButtonCreatRoomEvent();

	UFUNCTION(BlueprintCallable)
		void ButtonSureCreateRoom();

	UFUNCTION(BlueprintCallable)
		void ButtonCancelCreateRoom();

	UFUNCTION(BlueprintCallable)
		void ButtonEnterRoomEvent();

	UFUNCTION(BlueprintCallable)
		void ButtonReadyEvent();

	UFUNCTION(BlueprintCallable)
		void ButtonStartGameEvent();



public:
	//Canvas Main
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* Text_Username;

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

	// 干员界面的item
	UPROPERTY(BlueprintReadWrite)
		TArray<URoleItem*> RoleItemArray;

	// 在房间中的 item
	UPROPERTY(BlueprintReadWrite)
		TArray<URoomRoleItem*> RoomRoleItemArray;

	//当前选择的干员类型
	uint8 selectedRoleType;

	//Canvas Home
	UPROPERTY(Meta = (BindWidget))
		UCanvasPanel* CanvasHome;

	//Canvas Role
	UPROPERTY(Meta = (BindWidget))
		UCanvasPanel* CanvasRole;

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
		UTextBlock* Text_UnlockRoleSuccessfulName;

	UPROPERTY(Meta = (BindWidget))
		UCanvasPanel* CanvasRoleUnlockSuccessful;

	UPROPERTY(Meta = (BindWidget))
		UButton* Button_Role_Unlock_Successful_Back;

	//Room Menu
	UPROPERTY(Meta = (BindWidget))
		UButton* Button_Combat;

	UPROPERTY(Meta = (BindWidget))
		UCanvasPanel* CanvasRoomMenu;

	UPROPERTY(Meta = (BindWidget))
		UScrollBox* Scroll_Box_RoomList;

	UPROPERTY(EditAnywhere)
		TSubclassOf<URoomItem> RoomItemClass;

	UPROPERTY()
		TArray<URoomItem*> RoomItemGroup;

	//Room Create
	UPROPERTY(Meta = (BindWidget))
		UCanvasPanel* CanvasRoomCreate;

	UPROPERTY(Meta = (BindWidget))
		UEditableTextBox* EditableTextBox_RoomName;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* Text_TipCreateRoom;

	UPROPERTY(Meta = (BindWidget))
		UButton* Button_SureCreateRoom;

	//Room Enter
	UPROPERTY(Meta = (BindWidget))
		UButton* Button_EnterRoom;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* Text_Room_Menu_Tip;

	// Room Combat

	UPROPERTY(EditAnywhere)
		TSubclassOf<UPlayerItem> PlayerItemClass;

	UPROPERTY(Meta = (BindWidget))
		UCanvasPanel* CanvasRoom;

	UPROPERTY(Meta = (BindWidget))
		UScrollBox* Scroll_Box_TeamBlue;

	UPROPERTY(Meta = (BindWidget))
		UScrollBox* Scroll_Box_TeamRed;

	UPROPERTY()
		TArray<UPlayerItem*> PlayerItemGroupBlue;

	UPROPERTY()
		TArray<UPlayerItem*> PlayerItemGroupRed;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* Text_Room_Tip;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* Text_Button_Ready;

	UPROPERTY(Meta = (BindWidget))
		UButton* Button_StartGame;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* Text_Select_Role_Name;

	// Wait
	UPROPERTY(Meta = (BindWidget))
		UCanvasPanel* CanvasLoadingGame;


protected:
	// 干员界面 按钮
	void RoleItemSelect(uint8 RoleType, bool IsUnlock);

	// 房间界面 干员 
	void RoomRoleItemSelect(uint8 RoleType, bool IsUnlock);

	FString GetTimeStr();

	//选中的房间ID
	uint64 SelectRoomID;

	// 是否准备
	bool isReady;

	// 是否在房间中
	bool isInRoom;

	//将角色信息保存到本地
	TArray<FROLE_INFO> RoleList;
};
