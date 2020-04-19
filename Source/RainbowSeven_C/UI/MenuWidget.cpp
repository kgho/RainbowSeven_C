// Author : Kgho	Github : https://github.com/kgho


#include "MenuWidget.h"
#include "TextBlock.h"
#include "Scripts/ExCommon.h"
#include "ProgressBar.h"
#include "Button.h"
#include "RoleItem.h"
#include "LoginWidget.h"
#include "CanvasPanel.h"

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
	DDH::Debug() << "UMenuWidget::UnlockRoleSure selectedRoleType-->" << selectedRoleType << DDH::Endl();
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
