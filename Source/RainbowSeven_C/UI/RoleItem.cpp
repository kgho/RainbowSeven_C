﻿// Author : Kgho	Github : https://github.com/kgho


#include "RoleItem.h"
#include "Button.h"
#include "TextBlock.h"
#include "Scripts/ExCommon.h"

void URoleItem::RefreshItem(uint8 RoleID, uint8 isLock)
{
	DDH::Debug() << "URoleItem::RefreshItem--> isLock" << isLock << DDH::Endl();
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

void URoleItem::InitItemStyle()
{
	Button->SetStyle(RoleStyle);
	isUnlock = false;
}

void URoleItem::ButtonReleasedEvent()
{
	RoleItemSelectDel.ExecuteIfBound(RoleType, isUnlock);
}

