// Author : Kgho	Github : https://github.com/kgho

#include "LoginWidget.h"
#include "EditableTextBox.h"
#include "LoginGameMode.h"
#include "Engine/KBEMain.h"
#include "TextBlock.h"
#include "Scripts/ExCommon.h"

void ULoginWidget::InitWidget()
{
	Text_ClientVersion->SetText(FText::FromString("Cleint Version:" + UKBEMain::getClientVersion()));
	Text_ClientScriptVersion->SetText(FText::FromString("Client Script  Version:" + UKBEMain::getClientScriptVersion()));
	Text_ServerVersion->SetText(FText::FromString("Server  Version:" + UKBEMain::getServerVersion()));
	Text_ServerScriptVersion->SetText(FText::FromString("Server Scritp  Version:" + UKBEMain::getServerScriptVersion()));
}

void ULoginWidget::SignInButtonEvent()
{
	FString Username = EditableTextBox_Username->GetText().ToString();
	FString Password = EditableTextBox_Password->GetText().ToString();
	if (Username.IsEmpty() || Password.IsEmpty())
	{
		DDH::Debug() << "Username or Password can not be none!" << DDH::Endl();
		return;
	}
	//将用户名和密码转化为二进制数据
	TArray<uint8> LoginData;
	FString ProjectName("RainbowSeven");
	for (int i = 0; i < ProjectName.Len(); ++i) {
		LoginData.Add((uint8)ProjectName[i]);
	}
	LoginGameMode->KBEMain->login(Username, Password, LoginData);
}

void ULoginWidget::SignUpButtonEvent()
{
	FString Username = EditableTextBox_Username->GetText().ToString();
	FString Password = EditableTextBox_Password->GetText().ToString();
	if (Username.IsEmpty() || Password.IsEmpty())
	{
		DDH::Debug() << "Username or Password can not be none!" << DDH::Endl();
		return;
	}
	//将用户名和密码转化为二进制数据
	TArray<uint8> LoginData;
	FString ProjectName("RainbowSeven");
	for (int i = 0; i < ProjectName.Len(); ++i) {
		LoginData.Add((uint8)ProjectName[i]);
	}
	LoginGameMode->KBEMain->createAccount(Username, Password, LoginData);
}

