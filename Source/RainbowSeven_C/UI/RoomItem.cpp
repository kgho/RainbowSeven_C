// Author : Kgho	Github : https://github.com/kgho


#include "RoomItem.h"
#include "TextBlock.h"
#include "Image.h"

void URoomItem::ItemButtonEvent()
{
	ItemSelectDel.ExecuteIfBound(RoomInfo.RoomId);
}

void URoomItem::InitItem(FROOM_INFO InRoomInfo)
{
	RoomInfo = InRoomInfo;
	Text_Name->SetText(FText::FromString(RoomInfo.Name));
	ItemUnSelect();
}

void URoomItem::ItemSelect()
{
	IsSelected = true;
	Image_Outline->SetVisibility(ESlateVisibility::Visible);
}

void URoomItem::ItemUnSelect()
{
	IsSelected = false;
	Image_Outline->SetVisibility(ESlateVisibility::Hidden);
}