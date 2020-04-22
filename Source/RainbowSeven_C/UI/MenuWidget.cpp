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

void UMenuWidget::OnReqAccountInfo(uint16 level, uint64 exp, uint64 fame, uint64 coin)
{
	DDH::Debug() << "UMenuWidget::OnReqAccountInfo Coin-->" << coin << DDH::Endl();
	Text_Level->SetText(FText::FromString(FString::FromInt(level)));
	Text_Exp_Current->SetText(FText::FromString(FString::FromInt(exp)));
	Text_Exp_Total->SetText(FText::FromString(FString::FromInt(level * 100)));
	Text_Fame->SetText(FText::FromString(FString::FromInt(fame)));
	Text_Coin->SetText(FText::FromString(FString::FromInt(coin)));
	ProgressBar_Exp->SetPercent(exp / level * 100);

	for (size_t i = 0; i < RoleItemArray.Num(); i++)
	{
		DDH::Debug() << "UMenuWidget::OnReqAccountInfo RoleItemIndex-->" << i << DDH::Endl();
		RoleItemArray[i]->RoleItemSelectDel.BindUObject(this, &UMenuWidget::RoleItemSelect);
	}
}

void UMenuWidget::OnReqRoleList(TArray<FROLE_INFO> RoleList)
{
	DDH::Debug() << "UMenuWidget::OnReqAccountInfo RoleList.Num():-->" << RoleList.Num() << DDH::Endl();
	for (int32 i = 0; i < RoleList.Num(); i++)
	{
		uint8 RoleIndex = RoleList[i].RoleType - 1;
		DDH::Debug() << "UMenuWidget::OnReqAccountInfo I:-->" << i << ", isLock:" << RoleList[i].IsLock << DDH::Endl();
		DDH::Debug() << "UMenuWidget::OnReqAccountInfo RoleItemList:-->" << RoleItemArray.Num() << DDH::Endl();
		RoleItemArray[RoleIndex]->RefreshItem(RoleList[i].RoleType, RoleList[i].IsLock);
	}
}

void UMenuWidget::RefreshRoleInfo(FROLE_INFO RoleInfo)
{
	CanvasRoleInfo->SetVisibility(ESlateVisibility::Visible);

	switch (RoleInfo.RoleType)
	{
	case 1:
		Text_Role_Info_Name->SetText(FText::FromString("A"));
		break;
	case 2:
		Text_Role_Info_Name->SetText(FText::FromString("B"));
		break;
	case 3:
		Text_Role_Info_Name->SetText(FText::FromString("C"));
		break;
	case 4:
		Text_Role_Info_Name->SetText(FText::FromString("D"));
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
	DDH::Debug() << "UMenuWidget::OnReqUnlockRole--> Result:" << result << DDH::Endl();
	if (result == 0)
	{
		CanvasRoleUnlockSuccessful->SetVisibility(ESlateVisibility::Visible);
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
	DDH::Debug() << "UMenuWidget::UnlockRoleSure EventData->RoleType-->" << EventData->RoleType << DDH::Endl();
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
	CanvasRoomMenu->SetVisibility(ESlateVisibility::Hidden);
}

void UMenuWidget::ButtonRoleEvent()
{
	CanvasHome->SetVisibility(ESlateVisibility::Hidden);
	CanvasRole->SetVisibility(ESlateVisibility::Visible);
	CanvasRoomMenu->SetVisibility(ESlateVisibility::Hidden);
}

void UMenuWidget::ButtonCombatEvent()
{
	Button_SureCreateRoom->bIsEnabled = true;
	CanvasHome->SetVisibility(ESlateVisibility::Hidden);
	CanvasRole->SetVisibility(ESlateVisibility::Hidden);
	CanvasRoomMenu->SetVisibility(ESlateVisibility::Visible);
	ReqRoomList();
}

void UMenuWidget::ButtonRefreshRoomEvent()
{
	ReqRoomList();
}

void UMenuWidget::ButtonLeaveRoomEvent()
{
	KBENGINE_EVENT_FIRE("ReqLeaveRoom", NewObject<UKBEventData>());
	CanvasRoom->SetVisibility(ESlateVisibility::Hidden);
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
	CanvasRoom->SetVisibility(ESlateVisibility::Visible);

	//蓝队
	//把旧的从列表移除
	for (int i = 0; i < PlayerItemGroupBlue.Num(); ++i)
	{
		PlayerItemGroupBlue[i]->RemoveFromParent();
		PlayerItemGroupBlue[i]->ConditionalBeginDestroy();
	}
	//清空数组
	PlayerItemGroupBlue.Empty();

	Scroll_Box_TeamBlue->ClearChildren();

	for (int i = 0; i < PlayerListBlue.Num(); ++i)
	{
		// 创建PlayerItem
		UPlayerItem* PlayerItem = WidgetTree->ConstructWidget<UPlayerItem>(PlayerItemClass);
		UScrollBoxSlot* PlayerItemSlot = Cast<UScrollBoxSlot>(Scroll_Box_TeamBlue->AddChild(PlayerItem));
		PlayerItemSlot->SetPadding(FMargin(0.f, 5.f, 0.f, 5.f));

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
	Scroll_Box_TeamRed->ClearChildren();
	for (int i = 0; i < PlayerListRed.Num(); ++i)
	{
		UPlayerItem* PlayerItem = WidgetTree->ConstructWidget<UPlayerItem>(PlayerItemClass);
		UScrollBoxSlot* PlayerItemSlot = Cast<UScrollBoxSlot>(Scroll_Box_TeamRed->AddChild(PlayerItem));
		PlayerItemSlot->SetPadding(FMargin(0.f, 5.f, 0.f, 5.f));
		PlayerItem->RefreshItem(PlayerListRed[i]);
		//PlayerItem->ItemSelectDel.BindUObject(this, &UMenuWidget::RoomItemSelect);
		PlayerItemGroupRed.Add(PlayerItem);
	}
}

void UMenuWidget::ButtonCreatRoomEvent()
{
	CanvasRoomCreate->SetVisibility(ESlateVisibility::Visible);


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
	DDH::Debug() << "UMenuWidget::ButtonEnterRoomEvent RoomID-->" << EventData->RoomId << DDH::Endl();
	KBENGINE_EVENT_FIRE("ReqEnterRoom", EventData);
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
