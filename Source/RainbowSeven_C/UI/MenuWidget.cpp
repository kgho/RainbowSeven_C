// Author : Kgho	Github : https://github.com/kgho


#include "MenuWidget.h"
#include "TextBlock.h"
#include "Scripts/ExCommon.h"

void UMenuWidget::OnReqAccountInfo(uint16 level, uint64 exp, uint64 fame, uint64 coin)
{
	DDH::Debug() << "UMenuWidget::OnReqAccountInfo Coin-->" << coin << DDH::Endl();
	Text_Level->SetText(FText::FromString(FString::FromInt(level)));
	Text_Exp_Current->SetText(FText::FromString(FString::FromInt(exp)));
	Text_Fame->SetText(FText::FromString(FString::FromInt(fame)));
	Text_Coin->SetText(FText::FromString(FString::FromInt(coin)));
}