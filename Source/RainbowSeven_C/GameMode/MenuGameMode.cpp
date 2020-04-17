// Author : Kgho	Github : https://github.com/kgho


#include "MenuGameMode.h"
#include "Engine/KBEngine.h"
#include "Scripts/RSEventData.h"
#include "UI/MenuWidget.h"
#include "Scripts/ExCommon.h"

void AMenuGameMode::InstallEvent()
{
	Super::InstallEvent();

	KBENGINE_REGISTER_EVENT("OnReqAccountInfo", OnReqAccountInfo);
	KBENGINE_REGISTER_EVENT("OnReqRoleList", OnReqRoleList);
}

void AMenuGameMode::BeginPlay()
{
	MenuWidget = CreateWidget<UMenuWidget>(GetWorld(), MenuWidgetCalss);
	MenuWidget->AddToViewport();

	DDH::Debug() << "BeginPlay : AddToViewport-->" << DDH::Endl();

	Super::BeginPlay();
}

void AMenuGameMode::OnReqRoleList(const UKBEventData* EventData)
{
	const UKBEventData_OnReqRoleList* ServerData = Cast< UKBEventData_OnReqRoleList>(EventData);
}

void AMenuGameMode::OnReqAccountInfo(const UKBEventData* EventData)
{
	const UKBEventData_OnReqAccountInfo* ServerData = Cast< UKBEventData_OnReqAccountInfo>(EventData);

	DDH::Debug() << "AMenuGameMode::OnReqAccountInfo Coin-->" << ServerData->Coin << DDH::Endl();
	MenuWidget->OnReqAccountInfo(ServerData->Level, ServerData->Exp, ServerData->Fame, ServerData->Coin);
}

