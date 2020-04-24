// Author : Kgho	Github : https://github.com/kgho

#pragma once

#include "CoreMinimal.h"
#include "GameMode/KBEGameMode.h"
#include "CombatGameMode.generated.h"

/**
 * ��ʵ������˳��������ƶ��Ȼص��¼�
 */

class APlayerCharacter;
class ARemoteCharacter;
class ACharacterEntity;

UCLASS()
class RAINBOWSEVEN_C_API ACombatGameMode : public AKBEGameMode
{
	GENERATED_BODY()

public:

	UPROPERTY()
		APlayerCharacter* PlayerCharacter;

	// ���������
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<APlayerCharacter>> PlayerClassList;

	// Զ�������
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<ARemoteCharacter>> RemoteClassList;

	// �ֵ䱣�������еķ����ʵ�壬key��ʵ��ID,value����Ա��ɫָ��
	TMap<int32, ACharacterEntity*> CharacterMap;


public:
	virtual void UnInstallEvent() override;

protected:
	virtual void InstallEvent() override;

	virtual void BeginPlay() override;


	void OnEnterWorld(const UKBEventData* EventData);

	void OnEnterSpace(const UKBEventData* EventData);

	void OnLeaveWorld(const UKBEventData* EventData);

	void OnLeaveSpace(const UKBEventData* EventData);

	void SetPosition(const UKBEventData* EventData);

	void SetDirection(const UKBEventData* EventData);

	void UpdatePosition(const UKBEventData* EventData);

	void OnAnimUpdate(const UKBEventData* EventData);

	void SetBaseHP(const UKBEventData* EventData);

	void SetHP(const UKBEventData* EventData);

};
