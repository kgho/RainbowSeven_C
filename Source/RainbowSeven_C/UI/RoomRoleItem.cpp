// Author : Kgho	Github : https://github.com/kgho


#include "RoomRoleItem.h"
#include "Button.h"
#include "TextBlock.h"

void URoomRoleItem::RefreshItem(uint8 RoleID, uint8 isLock)
{
	if (isLock == 1)
	{
		Text_IsUnlock->SetVisibility(ESlateVisibility::Hidden);
		Button->SetBackgroundColor(FLinearColor(1.f, 1.f, 1.f, 1.f));
		Button->bIsEnabled = true;
		isUnlock = true;
	}
	else
	{
		Text_IsUnlock->SetVisibility(ESlateVisibility::Visible);
		Button->SetBackgroundColor(FLinearColor(.1f, .1f, .1f, 1));
		Button->bIsEnabled = false;
		isUnlock = false;
	}
}

void URoomRoleItem::InitItemStyle()
{
	Button->SetStyle(ButtonStyle);
	isUnlock = false;
}

void URoomRoleItem::ButtonReleasedEvent()
{
	//ItemSelectDel.ExecuteIfBound(RoleType, isUnlock);
}
