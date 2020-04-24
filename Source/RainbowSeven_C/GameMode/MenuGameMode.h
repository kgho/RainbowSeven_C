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

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void OnReqRoleList(const UKBEventData* EventData);

	void OnReqAccountInfo(const UKBEventData* EventData);

	void OnReqUnlockRole(const UKBEventData* EventData);

	void OnReqRoleInfo(const UKBEventData* EventData);

	// 请求房间列表回调函数
	void OnReqRoomList(const UKBEventData* EventData);

	// 创建房间回调函数
	void OnReqCreateRoom(const UKBEventData* EventData);

	// 进入房间回调函数
	void OnReqEnterRoom(const UKBEventData* EventData);

	void OnReqEnterRoomFailed(const UKBEventData* EventData);

	void OnReqEnterRoomFull(const UKBEventData* EventData);

	void OnReqLeaveRoom(const UKBEventData* EventData);

	void OnReqChangeState(const UKBEventData* EventData);

	void OnReqSelectRole(const UKBEventData* EventData);

	void OnAllReady(const UKBEventData* EventData);

	// 进入游戏地图
	void AddSpaceGeometryMapping(const UKBEventData* EventData);
};
