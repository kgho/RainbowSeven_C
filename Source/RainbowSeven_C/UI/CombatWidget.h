// Author : Kgho	Github : https://github.com/kgho

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CombatWidget.generated.h"

class UProgressBar;
class UCanvasPanel;
/**
 *
 */
UCLASS()
class RAINBOWSEVEN_C_API UCombatWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void InstallEvents(TArray<FString> BluePlayerNameArr, TArray<FString> RedPlayerNameArr);

	void UnInstallEvents();

	void SetHPPercent(float InPercent);

	void ToggleCanvasPanelScoreboard(bool isShow);

public:
	UPROPERTY(Meta = (BindWidget))
		UProgressBar* ProgressBar_Blood;

	UPROPERTY(Meta = (BindWidget))
		UCanvasPanel* CanvasPanelDeath;

	UPROPERTY(Meta = (BindWidget))
		UCanvasPanel* CanvasPanelScoreboard;

};
