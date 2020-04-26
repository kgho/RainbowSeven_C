// Author : Kgho	Github : https://github.com/kgho


#include "MenuWidget.h"
#include "TextBlock.h"
#include "Scripts/ExCommon.h"
#include "ProgressBar.h"
#include "Button.h"
#include "RoleItem.h"
#include "LoginWidget.h"
#include "CanvasPanel.h"
#include "RoomItem.h"
#include "WidgetTree.h"
#include "ScrollBox.h"
#include "ScrollBoxSlot.h"
#include "EditableTextBox.h"
#include <ctime>
#include "PlayerItem.h"
#include "VerticalBoxSlot.h"
#include "RoomRoleItem.h"
#include "VerticalBox.h"
#include "VerticalBoxSlot.h"

void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	DDH::Debug() << "UMenuWidget::NativeConstruct()" << DDH::Endl();
	for (size_t i = 0; i < RoleItemArray.Num(); i++)
	{
		RoleItemArray[i]->RoleItemSelectDel.BindUObject(this, &UMenuWidget::RoleItemSelect);
	}
	for (size_t i = 0; i < RoomRoleItemArray.Num(); i++)
	{
		RoomRoleItemArray[i]->ItemSelectDel.BindUObject(this, &UMenuWidget::RoomRoleItemSelect);
	}
}

void UMenuWidget::OnReqAccountInfo(FString name, uint16 level, uint64 exp, uint64 fame, uint64 coin)
{
	Text_Username->SetText(FText::FromString(name));
	Text_Level->SetText(FText::FromString(FString::FromInt(level)));
	Text_Exp_Current->SetText(FText::FromString(FString::FromInt(exp)));
	Text_Exp_Total->SetText(FText::FromString(FString::FromInt(level * 100)));
	Text_Fame->SetText(FText::FromString(FString::FromInt(fame)));
	Text_Coin->SetText(FText::FromString(FString::FromInt(coin)));
	ProgressBar_Exp->SetPercent(exp / level * 100);
}

void UMenuWidget::OnReqRoleList(TArray<FROLE_INFO> InRoleList)
{
	RoleList = InRoleList;
	for (int32 i = 0; i < InRoleList.Num(); i++)
	{
		uint8 RoleIndex = InRoleList[i].RoleType - 1;
		RoleItemArray[RoleIndex]->RefreshItem(InRoleList[i].RoleType, InRoleList[i].IsLock);
	}
}

void UMenuWidget::RefreshRoleInfo(FROLE_INFO RoleInfo)
{
	CanvasRoleInfo->SetVisibility(ESlateVisibility::Visible);

	switch (RoleInfo.RoleType)
	{
	case 1:
		Text_Role_Info_Name->SetText(FText::FromString(TEXT("埃里克")));
		break;
	case 2:
		Text_Role_Info_Name->SetText(FText::FromString(TEXT("卡拉")));
		break;
	case 3:
		Text_Role_Info_Name->SetText(FText::FromString(TEXT("克劳迪娅")));
		break;
	case 4:
		Text_Role_Info_Name->SetText(FText::FromString(TEXT("曼纽尔")));
		break;
	}

	uint32 playCount = RoleInfo.PlayCount;
	float averageKill = (float)RoleInfo.Kill / (float)playCount;
	float averageDeath = (float)RoleInfo.Death / (float)playCount;
	float averageAssist = (float)RoleInfo.Assist / (float)playCount;

	Text_KDA->SetText(FText::FromString(FString::SanitizeFloat((averageKill + averageAssist) / (averageDeath == 0 ? 0.5f : averageDeath))));
	Text_Role_Info_Kill->SetText(FText::FromString(FString::SanitizeFloat(averageKill)));
	Text_Role_Info_Death->SetText(FText::FromString(FString::SanitizeFloat(averageDeath)));
	Text_Role_Info_Assist->SetText(FText::FromString(FString::SanitizeFloat(averageAssist)));
	Text_Role_Info_PlayCount->SetText(FText::FromString(FString::FromInt(playCount)));
}

void UMenuWidget::OnReqUnlockRole(uint8 result)
{
	if (result == 0)
	{
		CanvasRoleUnlockSuccessful->SetVisibility(ESlateVisibility::Visible);

		FString selectRoleName;
		switch (selectedRoleType)
		{
		case 1:
			selectRoleName = TEXT("埃里克");
			break;
		case 2:
			selectRoleName = TEXT("卡拉");
			break;
		case 3:
			selectRoleName = TEXT("克劳迪娅");
			break;
		case 4:
			selectRoleName = TEXT("曼纽尔");
			break;
		}
		Text_UnlockRoleSuccessfulName->SetText(FText::FromString(selectRoleName));
	}
}

void UMenuWidget::CanvasRoleInfoHide()
{
	CanvasRoleInfo->SetVisibility(ESlateVisibility::Hidden);
}

void UMenuWidget::UnlockRoleSure()
{
	UKBEventData_ReqUnlockRole* EventData = NewObject<UKBEventData_ReqUnlockRole>();
	EventData->RoleType = selectedRoleType;
	KBENGINE_EVENT_FIRE("ReqUnlockRole", EventData);
}

void UMenuWidget::CanvasRoleUnlockBack()
{
	CanvasRoleUnlock->SetVisibility(ESlateVisibility::Hidden);
}

void UMenuWidget::RoleUnlockSuccessfulBack()
{
	CanvasRoleUnlock->SetVisibility(ESlateVisibility::Hidden);
	CanvasRoleUnlockSuccessful->SetVisibility(ESlateVisibility::Hidden);
	UKBEventData_ReqRoleList* EventData = NewObject<UKBEventData_ReqRoleList>();
	EventData->AccountName = "AccountName";
	KBENGINE_EVENT_FIRE("ReqRoleList", EventData);
}

void UMenuWidget::ButtonHomeEvent()
{
	CanvasHome->SetVisibility(ESlateVisibility::Visible);
	CanvasRole->SetVisibility(ESlateVisibility::Hidden);

	if (isInRoom)
	{
		CanvasRoomMenu->SetVisibility(ESlateVisibility::Hidden);
		CanvasRoom->SetVisibility(ESlateVisibility::Hidden);
	}
	else {
		CanvasRoomMenu->SetVisibility(ESlateVisibility::Hidden);
	}

}

void UMenuWidget::ButtonRoleEvent()
{
	CanvasHome->SetVisibility(ESlateVisibility::Hidden);
	CanvasRole->SetVisibility(ESlateVisibility::Visible);

	if (isInRoom)
	{
		CanvasRoomMenu->SetVisibility(ESlateVisibility::Hidden);
		CanvasRoom->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		CanvasRoomMenu->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UMenuWidget::ButtonCombatEvent()
{
	Button_SureCreateRoom->bIsEnabled = true;
	CanvasHome->SetVisibility(ESlateVisibility::Hidden);
	CanvasRole->SetVisibility(ESlateVisibility::Hidden);
	CanvasRoomMenu->SetVisibility(ESlateVisibility::Visible);

	// 更新干员按钮
	for (size_t i = 0; i < RoleList.Num(); i++)
	{
		uint8 RoleIndex = RoleList[i].RoleType - 1;
		RoomRoleItemArray[RoleIndex]->RefreshItem(RoleList[i].RoleType, RoleList[i].IsLock);
	}

	if (isInRoom)
	{
		CanvasRoom->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		ReqRoomList();
	}
}

void UMenuWidget::ButtonRefreshRoomEvent()
{
	ReqRoomList();
}

void UMenuWidget::ButtonLeaveRoomEvent()
{
	if (isReady)
	{
		Text_Room_Tip->SetText(FText::FromString(TEXT("请先取消准备后离开房间！")));
	}
	else
	{
		KBENGINE_EVENT_FIRE("ReqLeaveRoom", NewObject<UKBEventData>());
		Text_Room_Tip->SetText(FText::FromString(TEXT("正在离开房间......")));
	}
}

void UMenuWidget::OnReqRoomList(TArray<FROOM_INFO> RoomList)
{
	// 未选择房间隐藏 加入房间 按钮
	Button_EnterRoom->SetVisibility(ESlateVisibility::Hidden);

	//把旧的从列表移除
	for (int i = 0; i < RoomItemGroup.Num(); ++i)
	{
		RoomItemGroup[i]->RemoveFromParent();
		RoomItemGroup[i]->ConditionalBeginDestroy();
	}
	//清空数组
	RoomItemGroup.Empty();

	//循环创建RoomItem
	for (int i = 0; i < RoomList.Num(); ++i)
	{
		// 创建RoomItem
		URoomItem* RoomItem = WidgetTree->ConstructWidget<URoomItem>(RoomItemClass);
		UScrollBoxSlot* RoomItemSlot = Cast<UScrollBoxSlot>(Scroll_Box_RoomList->AddChild(RoomItem));
		RoomItemSlot->SetPadding(FMargin(0.f, 5.f, 0.f, 5.f));

		// 设置房间信息
		RoomItem->InitItem(RoomList[i]);
		RoomItem->ItemSelectDel.BindUObject(this, &UMenuWidget::RoomItemSelect);

		// 保存房间条目到本地数组
		RoomItemGroup.Add(RoomItem);
	}
}

void UMenuWidget::OnReqCreateRoom(FROOM_INFO RoomInfo)
{
	CanvasRoomCreate->SetVisibility(ESlateVisibility::Hidden);

	// 创建RoomItem
	URoomItem* RoomItem = WidgetTree->ConstructWidget<URoomItem>(RoomItemClass);
	UScrollBoxSlot* RoomItemSlot = Cast<UScrollBoxSlot>(Scroll_Box_RoomList->AddChild(RoomItem));
	RoomItemSlot->SetPadding(FMargin(0.f, 5.f, 0.f, 5.f));

	// 设置房间信息
	RoomItem->InitItem(RoomInfo);
	RoomItem->ItemSelectDel.BindUObject(this, &UMenuWidget::RoomItemSelect);

	// 保存房间条目到本地数组
	RoomItemGroup.Add(RoomItem);

	// 选中创建的房间
	RoomItemSelect(RoomItem->RoomInfo.RoomId);
}

void UMenuWidget::RoomItemSelect(uint64 RoomId)
{
	for (int i = 0; i < RoomItemGroup.Num(); ++i)
	{
		if (RoomItemGroup[i]->RoomInfo.RoomId != RoomId)
			RoomItemGroup[i]->ItemUnSelect();
		else
			RoomItemGroup[i]->ItemSelect();
	}
	SelectRoomID = RoomId;
	Button_EnterRoom->SetVisibility(ESlateVisibility::Visible);
}

void UMenuWidget::OnReqEnterRoom(TArray<FPLAYER_INFO> PlayerListBlue, TArray<FPLAYER_INFO> PlayerListRed)
{
	Text_Room_Tip->SetText(FText::FromString(TEXT("")));
	CanvasRoom->SetVisibility(ESlateVisibility::Visible);

	isInRoom = true;

	//蓝队
	//把旧的从列表移除
	for (int i = 0; i < PlayerItemGroupBlue.Num(); ++i)
	{
		PlayerItemGroupBlue[i]->RemoveFromParent();
		PlayerItemGroupBlue[i]->ConditionalBeginDestroy();
	}
	//清空数组
	PlayerItemGroupBlue.Empty();

	Vertical_Box_TeamBlue->ClearChildren();

	for (int i = 0; i < PlayerListBlue.Num(); ++i)
	{
		// 创建PlayerItem
		UPlayerItem* PlayerItem = WidgetTree->ConstructWidget<UPlayerItem>(PlayerItemClass);
		UVerticalBoxSlot* PlayerItemSlot = Cast<UVerticalBoxSlot>(Vertical_Box_TeamBlue->AddChild(PlayerItem));
		PlayerItemSlot->SetPadding(FMargin(5.f, 5.f, 5.f, 5.f));

		// 设置玩家信息
		PlayerItem->RefreshItem(PlayerListBlue[i]);
		//PlayerItem->ItemSelectDel.BindUObject(this, &UMenuWidget::RoomItemSelect);

		// 保存玩家条目到本地数组
		PlayerItemGroupBlue.Add(PlayerItem);
	}

	//红队
	for (int i = 0; i < PlayerItemGroupRed.Num(); ++i)
	{
		PlayerItemGroupRed[i]->RemoveFromParent();
		PlayerItemGroupRed[i]->ConditionalBeginDestroy();
	}
	PlayerItemGroupRed.Empty();
	Vertical_Box_TeamRed->ClearChildren();
	for (int i = 0; i < PlayerListRed.Num(); ++i)
	{
		UPlayerItem* PlayerItem = WidgetTree->ConstructWidget<UPlayerItem>(PlayerItemClass);
		UVerticalBoxSlot* PlayerItemSlot = Cast<UVerticalBoxSlot>(Vertical_Box_TeamRed->AddChild(PlayerItem));
		PlayerItemSlot->SetPadding(FMargin(5.f, 5.f, 5.f, 5.f));
		PlayerItem->RefreshItem(PlayerListRed[i]);
		//PlayerItem->ItemSelectDel.BindUObject(this, &UMenuWidget::RoomItemSelect);
		PlayerItemGroupRed.Add(PlayerItem);
	}

	//进入放进后自动选择第一个干员
	UKBEventData_ReqSelectRole* EventData = NewObject<UKBEventData_ReqSelectRole>();
	EventData->RoleType = 1;
	KBENGINE_EVENT_FIRE("ReqSelectRole", EventData);
}

void UMenuWidget::OnReqChangeState(uint8 state)
{
	if (state == 1)
	{
		isReady = true;
		Text_Button_Ready->SetText(FText::FromString(TEXT("取消准备")));
	}
	else
	{
		isReady = false;
		Text_Button_Ready->SetText(FText::FromString(TEXT("准备")));
	}
}

void UMenuWidget::OnReqSelectRole(uint8 roleType)
{
	FString selectRoleName;
	switch (roleType)
	{
	case 1:
		selectRoleName = TEXT("埃里克");
		break;
	case 2:
		selectRoleName = TEXT("卡拉");
		break;
	case 3:
		selectRoleName = TEXT("克劳迪娅");
		break;
	case 4:
		selectRoleName = TEXT("曼纽尔");
		break;
	}
	Text_Select_Role_Name->SetText(FText::FromString(selectRoleName));
	for (int i = 0; i < RoomRoleItemArray.Num(); ++i)
	{
		if (RoomRoleItemArray[i]->RoleType != roleType)
			RoomRoleItemArray[i]->ItemUnSelect();
		else
			RoomRoleItemArray[i]->ItemSelect();
	}
	Text_Room_Tip->SetText(FText::FromString(TEXT("已选择干员：") + selectRoleName));
}

void UMenuWidget::OnAllReady(uint8 allReady)
{
	if (allReady == 0)
	{
		Button_StartGame->SetVisibility(ESlateVisibility::Visible);
	}
	else {
		Button_StartGame->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UMenuWidget::ButtonCreatRoomEvent()
{
	CanvasRoomCreate->SetVisibility(ESlateVisibility::Visible);
	Text_TipCreateRoom->SetText(FText::FromString(TEXT("")));
	EditableTextBox_RoomName->SetText(FText::FromString(TEXT("肃清模式--木屋  ") + GetTimeStr()));
}

void UMenuWidget::ButtonSureCreateRoom()
{
	FString roomNameStr = EditableTextBox_RoomName->Text.ToString();

	if (roomNameStr.IsEmpty())
	{
		Text_TipCreateRoom->SetText(FText::FromString(TEXT("房间名称不能未空！")));
		EditableTextBox_RoomName->SetText(FText::FromString(TEXT("肃清模式--木屋  ") + GetTimeStr()));
		return;
	}

	UKBEventData_ReqCreateRoom* EventData = NewObject<UKBEventData_ReqCreateRoom>();
	EventData->RoomName = roomNameStr;
	KBENGINE_EVENT_FIRE("ReqCreateRoom", EventData);
	Button_SureCreateRoom->bIsEnabled = false;
	Text_TipCreateRoom->SetText(FText::FromString(TEXT("正在创建房间...")));
}

void UMenuWidget::ButtonCancelCreateRoom()
{
	CanvasRoomCreate->SetVisibility(ESlateVisibility::Hidden);
}

void UMenuWidget::ButtonEnterRoomEvent()
{
	Text_Room_Menu_Tip->SetText(FText::FromString(TEXT("正在进入房间......")));
	UKBEventData_ReqEnterRoom* EventData = NewObject<UKBEventData_ReqEnterRoom>();
	EventData->RoomId = SelectRoomID;

	KBENGINE_EVENT_FIRE("ReqEnterRoom", EventData);
}

void UMenuWidget::ButtonReadyEvent()
{
	if (isReady)
	{
		Text_Room_Tip->SetText(FText::FromString(TEXT("正在请求取消准备......")));
	}
	else
	{
		Text_Room_Tip->SetText(FText::FromString(TEXT("正在请求进入准备......")));
	}
	ReqChangeState();
}

void UMenuWidget::ButtonStartGameEvent()
{
	CanvasLoadingGame->SetVisibility(ESlateVisibility::Visible);
	ReqStartGame();
}

void UMenuWidget::ReqStartGame()
{
	KBENGINE_EVENT_FIRE("ReqStartGame", NewObject<UKBEventData>());
}

void UMenuWidget::LoadGame()
{

}

void UMenuWidget::ReqRoomList()
{
	KBENGINE_EVENT_FIRE("ReqRoomList", NewObject<UKBEventData>());
}

void UMenuWidget::RoleItemSelect(uint8 RoleType, bool IsUnlock)
{
	selectedRoleType = RoleType;

	if (IsUnlock)
	{
		CanvasRoleInfo->SetVisibility(ESlateVisibility::Visible);
		UKBEventData_ReqRoleInfo* EventData = NewObject<UKBEventData_ReqRoleInfo>();
		EventData->RoleType = RoleType;
		KBENGINE_EVENT_FIRE("ReqRoleInfo", EventData);
	}
	else
	{
		CanvasRoleUnlock->SetVisibility(ESlateVisibility::Visible);

		FString selectRoleName;
		switch (selectedRoleType)
		{
		case 1:
			selectRoleName = TEXT("埃里克");
			break;
		case 2:
			selectRoleName = TEXT("卡拉");
			break;
		case 3:
			selectRoleName = TEXT("克劳迪娅");
			break;
		case 4:
			selectRoleName = TEXT("曼纽尔");
			break;
		}
		Text_Role_Unlock_Name->SetText(FText::FromString(selectRoleName));
	}
}

void UMenuWidget::OnReqEnterRoomFailed()
{
	Text_Room_Menu_Tip->SetText(FText::FromString(TEXT("进入失败，请稍后重试......")));
}

void UMenuWidget::OnReqEnterRoomFull()
{
	Text_Room_Menu_Tip->SetText(FText::FromString(TEXT("房间人数已满，请选择其它房间进入......")));
}

void UMenuWidget::OnReqLeaveRoom()
{
	Text_Room_Menu_Tip->SetText(FText::FromString(TEXT("成功离开房间......")));
	CanvasRoom->SetVisibility(ESlateVisibility::Hidden);
	isInRoom = false;
}

void UMenuWidget::ReqChangeState()
{

	UKBEventData_ReqChangeState* EventData = NewObject<UKBEventData_ReqChangeState>();
	EventData->State = isReady ? 0 : 1;
	KBENGINE_EVENT_FIRE("ReqChangeState", EventData);
}

void UMenuWidget::RoomRoleItemSelect(uint8 RoleType, bool IsUnlock)
{
	DDH::Debug() << "UMenuWidget::RoomRoleItemSelect--> RoleType:" << RoleType << DDH::Endl();
	if (IsUnlock)
	{
		UKBEventData_ReqSelectRole* EventData = NewObject<UKBEventData_ReqSelectRole>();
		EventData->RoleType = RoleType;
		KBENGINE_EVENT_FIRE("ReqSelectRole", EventData);
	}
	else
	{
		Text_Room_Tip->SetText(FText::FromString(TEXT("该干员未解锁！")));
	}
}

FString UMenuWidget::GetTimeStr()
{
	// 基于当前系统的当前日期/时间
	//time_t now = time(0);
	// 把 now 转换为字符串形式
	//FString dt = ctime(&now);

	// 基于当前系统的当前日期/时间
	time_t now = time(0);

	tm* ltm = localtime(&now);

	// 年
	FString year = FString::FromInt(1900 + ltm->tm_year);

	// 月
	FString month = FString::FromInt(1 + ltm->tm_mon);
	month = month.Len() == 1 ? "0" + month : month;

	// 日
	FString day = FString::FromInt(ltm->tm_mday);
	day = day.Len() == 1 ? "0" + day : day;

	// 时
	FString hour = FString::FromInt(ltm->tm_hour);
	hour = hour.Len() == 1 ? "0" + hour : hour;

	// 分
	FString minute = FString::FromInt(ltm->tm_min);
	minute = minute.Len() == 1 ? "0" + minute : minute;

	// 秒
	FString second = FString::FromInt(ltm->tm_sec);
	second = second.Len() == 1 ? "0" + second : second;

	FString timeStr = year + "/" + month + "/" + day + "	" + hour + ":" + minute + ":" + second;

	return timeStr;
}
