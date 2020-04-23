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

	// ���󷿼��б�ص�����
	void OnReqRoomList(const UKBEventData* EventData);

	// ��������ص�����
	void OnReqCreateRoom(const UKBEventData* EventData);

	// ���뷿��ص�����
	void OnReqEnterRoom(const UKBEventData* EventData);

	void OnReqEnterRoomFailed(const UKBEventData* EventData);

	void OnReqEnterRoomFull(const UKBEventData* EventData);

	void OnReqLeaveRoom(const UKBEventData* EventData);

	void OnReqChangeState(const UKBEventData* EventData);

	void OnReqSelectRole(const UKBEventData* EventData);

	void OnAllReady(const UKBEventData* EventData);

	// ������Ϸ��ͼ
	void AddSpaceGeometryMapping(const UKBEventData* EventData);
};
