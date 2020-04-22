// Author : Kgho	Github : https://github.com/kgho


#include "PlayerItem.h"
#include "TextBlock.h"

void UPlayerItem::RefreshItem(FPLAYER_INFO InPlayerInfo)
{
	Text_Username->SetText(FText::FromString(InPlayerInfo.Name));
	Text_State->SetText(FText::FromString(InPlayerInfo.State == 0 ? TEXT("未准备") : TEXT("已准备")));
	Text_Level->SetText(FText::FromString(FString::FromInt(InPlayerInfo.Levle)));

	if (InPlayerInfo.Master == 1)
	{
		Text_Master->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Text_Master->SetVisibility(ESlateVisibility::Hidden);
	}
}