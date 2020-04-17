// Author : Kgho	Github : https://github.com/kgho

#pragma once

#include "CoreMinimal.h"
#include "GameMode/KBEGameMode.h"
#include "MenuGameMode.generated.h"

class UMenuWidget;

/**
 *
 */
UCLASS()
class RAINBOWSEVEN_C_API AMenuGameMode : public AKBEGameMode
{
	GENERATED_BODY()

public:
	virtual void InstallEvent() override;

public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UMenuWidget> MenuWidgetCalss;

	UMenuWidget* MenuWidget;

protected:
	virtual void BeginPlay() override;

	void OnReqRoleList(const UKBEventData* EventData);
};
