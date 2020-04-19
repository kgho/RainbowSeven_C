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
	KBENGINE_REGISTER_EVENT("OnReqUnlockRole", OnReqUnlockRole);
	KBENGINE_REGISTER_EVENT("OnReqRoleInfo", OnReqRoleInfo);

	KBENGINE_REGISTER_EVENT("OnReqRoomList", OnReqRoomList);
	KBENGINE_REGISTER_EVENT("OnCreateRoom", OnCreateRoom);
}

void AMenuGameMode::BeginPlay()
{
	MenuWidget = CreateWidget<UMenuWidget>(GetWorld(), MenuWidgetCalss);
	MenuWidget->AddToViewport();

	Super::BeginPlay();
}

void AMenuGameMode::OnReqRoleList(const UKBEventData* EventData)
{
	const UKBEventData_OnReqRoleList* ServerData = Cast<UKBEventData_OnReqRoleList>(EventData);

	MenuWidget->OnReqRoleList(ServerData->RoleList);
}

void AMenuGameMode::OnReqAccountInfo(const UKBEventData* EventData)
{
	const UKBEventData_OnReqAccountInfo* ServerData = Cast<UKBEventData_OnReqAccountInfo>(EventData);

	DDH::Debug() << "AMenuGameMode::OnReqAccountInfo Coin-->" << ServerData->Coin << DDH::Endl();
	MenuWidget->OnReqAccountInfo(ServerData->Level, ServerData->Exp, ServerData->Fame, ServerData->Coin);
}

void AMenuGameMode::OnReqUnlockRole(const UKBEventData* EventData)
{
	const UKBEventData_OnReqUnlockRole* ServerData = Cast<UKBEventData_OnReqUnlockRole>(EventData);
	DDH::Debug() << "AMenuGameMode::OnReqUnlockRole Result-->" << ServerData->Result << DDH::Endl();
	MenuWidget->OnReqUnlockRole(ServerData->Result);
}

void AMenuGameMode::OnReqRoleInfo(const UKBEventData* EventData)
{
	const UKBEventData_OnReqRoleInfo* ServerData = Cast<UKBEventData_OnReqRoleInfo>(EventData);
	DDH::Debug() << "AMenuGameMode::OnReqRoleInfo Kill-->" << uint64(ServerData->RoleInfo.Kill) << DDH::Endl();
	MenuWidget->RefreshRoleInfo(ServerData->RoleInfo);
}

void AMenuGameMode::OnReqRoomList(const UKBEventData* EventData)
{
	const UKBEventData_OnReqRoomList* ServerData = Cast<UKBEventData_OnReqRoomList>(EventData);
	DDH::Debug() << "AMenuGameMode::OnReqRoomList-->" << ServerData->RoomList.Num() << DDH::Endl();
	MenuWidget->OnReqRoomList(ServerData->RoomList);
}

void AMenuGameMode::OnCreateRoom(const UKBEventData* EventData)
{
	const UKBEventData_OnCreateRoom* ServerData = Cast<UKBEventData_OnCreateRoom>(EventData);
	DDH::Debug() << "AMenuGameMode::OnCreateRoom -->" << ServerData->RoomInfo.Name << DDH::Endl();
}

