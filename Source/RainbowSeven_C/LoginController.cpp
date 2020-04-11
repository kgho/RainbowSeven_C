// Author : Kgho	Github : https://github.com/kgho


#include "LoginController.h"

void ALoginController::BeginPlay()
{
	Super::BeginPlay();

	//设置窗口大小 r.setres 960x540w  窗口模式
	ConsoleCommand(FString::Printf(TEXT("r.setres %dx%dw"), ScreenWidth, ScreenHeight));
	bShowMouseCursor = true;

	//设置输入模式
	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputMode);
}

