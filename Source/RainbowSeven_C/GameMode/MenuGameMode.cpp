// Author : Kgho	Github : https://github.com/kgho


#include "MenuGameMode.h"
#include "Engine/KBEngine.h"
#include "Scripts/RSEventData.h"
#include "UI/MenuWidget.h"
#include "Scripts/ExCommon.h"
#include "Kismet/GameplayStatics.h"
#include "RSGameInstance.h"

void AMenuGameMode::InstallEvent()
{
	Super::InstallEvent();

	KBENGINE_REGISTER_EVENT("OnReqAccountInfo", OnReqAccountInfo);

	KBENGINE_REGISTER_EVENT("OnReqRoleList", OnReqRoleList);
	KBENGINE_REGISTER_EVENT("OnReqUnlockRole", OnReqUnlockRole);
	KBENGINE_REGISTER_EVENT("OnReqRoleInfo", OnReqRoleInfo);

	KBENGINE_REGISTER_EVENT("OnReqRoomList", OnReqRoomList);
	KBENGINE_REGISTER_EVENT("OnReqCreateRoom", OnReqCreateRoom);

	KBENGINE_REGISTER_EVENT("OnReqEnterRoom", OnReqEnterRoom);
	KBENGINE_REGISTER_EVENT("OnReqEnterRoomFailed", OnReqEnterRoomFailed);
	KBENGINE_REGISTER_EVENT("OnReqEnterRoomFull", OnReqEnterRoomFull);

	KBENGINE_REGISTER_EVENT("OnReqLeaveRoom", OnReqLeaveRoom);

	KBENGINE_REGISTER_EVENT("OnReqChangeState", OnReqChangeState);

	KBENGINE_REGISTER_EVENT("OnReqSelectRole", OnReqSelectRole);

	KBENGINE_REGISTER_EVENT("OnAllReady", OnAllReady);

	KBENGINE_REGISTER_EVENT("OnReqStartGame", OnReqStartGame);

	// 进入游戏地图
	KBENGINE_REGISTER_EVENT("addSpaceGeometryMapping", AddSpaceGeometryMapping);
}

void AMenuGameMode::BeginPlay()
{
	MenuWidget = CreateWidget<UMenuWidget>(GetWorld(), MenuWidgetCalss);
	MenuWidget->AddToViewport();

	Super::BeginPlay();
}

void AMenuGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AMenuGameMode::OnReqRoleList(const UKBEventData* EventData)
{
	const UKBEventData_OnReqRoleList* ServerData = Cast<UKBEventData_OnReqRoleList>(EventData);

	MenuWidget->OnReqRoleList(ServerData->RoleList);
}

void AMenuGameMode::OnReqAccountInfo(const UKBEventData* EventData)
{
	const UKBEventData_OnReqAccountInfo* ServerData = Cast<UKBEventData_OnReqAccountInfo>(EventData);
	MenuWidget->OnReqAccountInfo(ServerData->Name, ServerData->Level, ServerData->Exp, ServerData->Fame, ServerData->Coin);
}

void AMenuGameMode::OnReqUnlockRole(const UKBEventData* EventData)
{
	const UKBEventData_OnReqUnlockRole* ServerData = Cast<UKBEventData_OnReqUnlockRole>(EventData);
	DDH::Debug() << "AMenuGameMode::OnReqUnlockRole Result-->" << ServerData->Result << DDH::Endl();
	MenuWidget->OnReqUnlockRole(ServerData->Result, ServerData->RoleType);
}

void AMenuGameMode::OnReqRoleInfo(const UKBEventData* EventData)
{
	const UKBEventData_OnReqRoleInfo* ServerData = Cast<UKBEventData_OnReqRoleInfo>(EventData);
	MenuWidget->RefreshRoleInfo(ServerData->RoleInfo);
}

void AMenuGameMode::OnReqRoomList(const UKBEventData* EventData)
{
	const UKBEventData_OnReqRoomList* ServerData = Cast<UKBEventData_OnReqRoomList>(EventData);
	DDH::Debug() << "AMenuGameMode::OnReqRoomList-->" << ServerData->RoomList.Num() << DDH::Endl();
	MenuWidget->OnReqRoomList(ServerData->RoomList);
}

void AMenuGameMode::OnReqCreateRoom(const UKBEventData* EventData)
{
	const UKBEventData_OnReqCreateRoom* ServerData = Cast<UKBEventData_OnReqCreateRoom>(EventData);
	DDH::Debug() << "AMenuGameMode::OnReqCreateRoom -->" << ServerData->RoomInfo.Name << DDH::Endl();
	MenuWidget->OnReqCreateRoom(ServerData->RoomInfo);
}

void AMenuGameMode::OnReqEnterRoom(const UKBEventData* EventData)
{
	const UKBEventData_OnReqEnterRoom* ServerData = Cast<UKBEventData_OnReqEnterRoom>(EventData);
	DDH::Debug() << "AMenuGameMode::OnReqEnterRoom PlayerBlueNum-->" << ServerData->PlayerListBlue.Num() << ", PlayerRedNum-->" << ServerData->PlayerListRed.Num() << DDH::Endl();
	MenuWidget->OnReqEnterRoom(ServerData->PlayerListBlue, ServerData->PlayerListRed);
}

void AMenuGameMode::OnReqEnterRoomFailed(const UKBEventData* EventData)
{
	MenuWidget->OnReqEnterRoomFailed();
}

void AMenuGameMode::OnReqEnterRoomFull(const UKBEventData* EventData)
{
	MenuWidget->OnReqEnterRoomFull();
}

void AMenuGameMode::OnReqLeaveRoom(const UKBEventData* EventData)
{
	MenuWidget->OnReqLeaveRoom();
}

void AMenuGameMode::OnReqChangeState(const UKBEventData* EventData)
{
	const UKBEventData_OnReqChangeState* ServerData = Cast<UKBEventData_OnReqChangeState>(EventData);
	MenuWidget->OnReqChangeState(ServerData->State);
}

void AMenuGameMode::OnReqSelectRole(const UKBEventData* EventData)
{
	const UKBEventData_OnReqSelectRole* ServerData = Cast<UKBEventData_OnReqSelectRole>(EventData);
	MenuWidget->OnReqSelectRole(ServerData->RoleType);
}

void AMenuGameMode::OnAllReady(const UKBEventData* EventData)
{
	const UKBEventData_OnAllReady* ServerData = Cast<UKBEventData_OnAllReady>(EventData);
	MenuWidget->OnAllReady(ServerData->AllReady);
}

void AMenuGameMode::OnReqStartGame(const UKBEventData* EventData)
{
	//保存选中的房间名字到GameInstance
	URSGameInstance* GameInstance = Cast<URSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GameInstance->BluePlayerNameArr = { TEXT("Blue 1"), TEXT("Blue 2"), TEXT("Blue 3") , TEXT("Blue 4") , TEXT("Blue 5") };
	GameInstance->RedPlayerNameArr = { TEXT("Red 1"), TEXT("Red 2"), TEXT("Red 3"), TEXT("Red 4"), TEXT("Red 5") };
}

void AMenuGameMode::AddSpaceGeometryMapping(const UKBEventData* EventData)
{
	const UKBEventData_addSpaceGeometryMapping* ServerData = Cast<UKBEventData_addSpaceGeometryMapping>(EventData);

	FString MapName; // GameMap
	FString TempStr;
	ServerData->spaceResPath.Split("/", &TempStr, &MapName);

	UGameplayStatics::OpenLevel(GetWorld(), FName(*MapName));
}

