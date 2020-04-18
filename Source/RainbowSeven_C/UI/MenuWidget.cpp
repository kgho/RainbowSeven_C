// Author : Kgho	Github : https://github.com/kgho


#include "MenuWidget.h"
#include "TextBlock.h"
#include "Scripts/ExCommon.h"
#include "ProgressBar.h"
#include "Button.h"
#include "RoleItem.h"

void UMenuWidget::OnReqAccountInfo(uint16 level, uint64 exp, uint64 fame, uint64 coin)
{
	DDH::Debug() << "UMenuWidget::OnReqAccountInfo Coin-->" << coin << DDH::Endl();
	Text_Level->SetText(FText::FromString(FString::FromInt(level)));
	Text_Exp_Current->SetText(FText::FromString(FString::FromInt(exp)));
	Text_Exp_Total->SetText(FText::FromString(FString::FromInt(level * 100)));
	Text_Fame->SetText(FText::FromString(FString::FromInt(fame)));
	Text_Coin->SetText(FText::FromString(FString::FromInt(coin)));
	ProgressBar_Exp->SetPercent(exp / level * 100);
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
