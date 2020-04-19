// Author : Kgho	Github : https://github.com/kgho

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoginWidget.generated.h"

class UEditableTextBox;
class UTextBlock;
class ALoginGameMode;
/**
*
*/
UCLASS()
class RAINBOWSEVEN_C_API ULoginWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void InitWidget();

	UFUNCTION(BlueprintCallable)
		void SignInButtonEvent();

	UFUNCTION(BlueprintCallable)
		void SignUpButtonEvent();

public:
	ALoginGameMode* LoginGameMode;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* Text_ClientVersion;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* Text_ClientScriptVersion;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* Text_ServerVersion;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* Text_ServerScriptVersion;

	UPROPERTY(Meta = (BindWidget))
		UEditableTextBox* EditableTextBox_Username;

	UPROPERTY(Meta = (BindWidget))
		UEditableTextBox* EditableTextBox_Password;

	FString AccountName;
};
