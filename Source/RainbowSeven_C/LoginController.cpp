// Author : Kgho	Github : https://github.com/kgho


#include "LoginController.h"

void ALoginController::BeginPlay()
{
	Super::BeginPlay();

	//���ô��ڴ�С r.setres 960x540w  ����ģʽ
	ConsoleCommand(FString::Printf(TEXT("r.setres %dx%dw"), ScreenWidth, ScreenHeight));
	bShowMouseCursor = true;

	//��������ģʽ
	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputMode);
}

