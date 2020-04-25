// Author : Kgho	Github : https://github.com/kgho


#include "CombatWidget.h"
#include "Engine/KBEngine.h"
#include "Scripts/RSEventData.h"
#include "ProgressBar.h"
#include "CanvasPanel.h"

void UCombatWidget::InstallEvents(TArray<FString> BluePlayerNameArr, TArray<FString> RedPlayerNameArr)
{
	// 设置 计分面板 玩家名称
}

void UCombatWidget::UnInstallEvents()
{
	KBENGINE_DEREGISTER_ALL_EVENT();
}

void UCombatWidget::SetHPPercent(float InPercent)
{
	ProgressBar_Blood->SetPercent(InPercent);

	ProgressBar_Blood->SetPercent(InPercent);
	ProgressBar_Blood->SetFillColorAndOpacity(FLinearColor(1.f - InPercent, InPercent, 0.f));

	//如果血值为0, 显示死亡 UI
	if (InPercent <= 0.f)
	{
		CanvasPanelDeath->SetVisibility(ESlateVisibility::Hidden);
	}
}
