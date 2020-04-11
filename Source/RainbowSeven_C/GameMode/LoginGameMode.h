// Author : Kgho	Github : https://github.com/kgho

#pragma once

#include "CoreMinimal.h"
#include "KBEGameMode.h"
#include "LoginGameMode.generated.h"

class UKBEMain;
class ULoginWidget;
class UKBEventData;
/**
*
*/
UCLASS()
class RAINBOWSEVEN_C_API ALoginGameMode : public AKBEGameMode
{
	GENERATED_BODY()

public:
	virtual void InstallEvent() override;

public:
	UKBEMain* KBEMain;

protected:
	virtual void BeginPlay() override;

	//KBEÊÂ¼þ
	void OnCreateAccountResult(const UKBEventData* pEventData);

	void OnLoginFailed(const UKBEventData* pEventData);

	void OnVersionNotMatch(const UKBEventData* pEventData);

	void OnScriptVersionNotMatch(const UKBEventData* pEventData);

	void OnLoginBaseappFailed(const UKBEventData* pEventData);

	void OnLoginBaseapp(const UKBEventData* pEventData);

	void OnLoginSuccessfully(const UKBEventData* pEventData);

protected:
	ULoginWidget* LoginWidget;
	UPROPERTY(EditAnywhere)
		TSubclassOf<ULoginWidget> LoginWidgetClass;
};
