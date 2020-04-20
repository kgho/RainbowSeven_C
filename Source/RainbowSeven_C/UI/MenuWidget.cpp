﻿// Author : Kgho	Github : https://github.com/kgho


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

void UMenuWidget::OnReqRoomList(TArray<FROOM_INFO> RoomList)
{
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
		//RoomItem->RoomItemSelectDel.BindUObject(this, &UExRoomWidget::RoomItemSelect);

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
	//RoomItem->RoomItemSelectDel.BindUObject(this, &UExRoomWidget::RoomItemSelect);

	// 保存房间条目到本地数组
	RoomItemGroup.Add(RoomItem);
}

void UMenuWidget::ButtonCreatRoomEvent()
{
	CanvasRoomCreate->SetVisibility(ESlateVisibility::Visible);

	//// 基于当前系统的当前日期/时间
	//time_t now = time(0);
	//// 把 now 转换为字符串形式
	//FString dt = ctime(&now);

	// 基于当前系统的当前日期/时间
	time_t now = time(0);

	tm* ltm = localtime(&now);

	// 年
	FString year = FString::FromInt(1900 + ltm->tm_year);
	// 月
	FString month = FString::FromInt(1 + ltm->tm_mon);
	// 日
	FString day = FString::FromInt(ltm->tm_mday);
	// 时
	FString hour = FString::FromInt(ltm->tm_hour);
	// 分
	FString minute = FString::FromInt(ltm->tm_min);
	// 秒
	FString second = FString::FromInt(ltm->tm_sec);

	FString timeStr = year + "年" + month + "月";
	EditableTextBox_RoomName->SetText(FText::FromString("肃清模式---木屋---" + year + "/" + month + "/" + day + "	" + hour + ":" + minute + ":" + second));
}

void UMenuWidget::ButtonSureCreateRoom()
{
	FString roomNameStr = EditableTextBox_RoomName->Text.ToString();

	if (roomNameStr.IsEmpty())
	{
		Text_TipCreateRoom->SetText(FText::FromString("房间名称不能未空！"));
		return;
	}

	UKBEventData_ReqCreateRoom* EventData = NewObject<UKBEventData_ReqCreateRoom>();
	EventData->RoomName = roomNameStr;
	KBENGINE_EVENT_FIRE("ReqCreateRoom", EventData);
	Button_SureCreateRoom->bIsEnabled = false;
	Text_TipCreateRoom->SetText(FText::FromString("正在创建房间..."));
}

void UMenuWidget::ButtonCancelCreateRoom()
{
	CanvasRoomCreate->SetVisibility(ESlateVisibility::Hidden);
}

void UMenuWidget::EnterRoomEvent()
{
}

void UMenuWidget::ReqRoomList()
{
	KBENGINE_EVENT_FIRE("ReqRoomList", NewObject<UKBEventData>());
}



void UMenuWidget::RoleItemSelect(uint8 RoleType, bool IsUnlock)
{
	selectedRoleType = RoleType;
	DDH::Debug() << "UMenuWidget::RoleItemSelect RoleType-->" << selectedRoleType << DDH::Endl();

	DDH::Debug() << "UMenuWidget::RoleItemSelect IsUnlock-->" << IsUnlock << DDH::Endl();
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
