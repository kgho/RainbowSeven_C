// Author : Kgho	Github : https://github.com/kgho

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterEntity.generated.h"

class ACombatGameMode;
/**
 * KBE��ɫ��ʵ���Ӧ��UE4��ɫ�Ļ���, ����ʵ��id, ʵ��ʵ��, �ƶ�����, ��������, ��������ʵ�־�����ƶ�ͬ���߼�
 */
UCLASS()
class RAINBOWSEVEN_C_API ACharacterEntity : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterEntity();

	virtual void Destroyed() override;

	void SetTargetPosition(FVector InPos);

	void SetTargetRotator(FRotator InRot);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	int32 EntityId;

	uint8 RoleType;

	FString RoleName;

	ACombatGameMode* CombatGameMode;

	bool IsPlayer;

	UPROPERTY(BlueprintReadOnly)
		float AnimSpeed;

	UPROPERTY(BlueprintReadOnly)
		float AnimDirection;

	UPROPERTY(BlueprintReadOnly)
		bool AnimIsInAir;

	// ͨ��Ѫ������������������
	UPROPERTY(BlueprintReadOnly)
		int32 HP;

protected:

	//Ŀ��λ��
	FVector TargetPosition;

	//Ŀ����ת
	FRotator TargetRotator;

	//��һ�θ���λ�õ�ʱ��
	float LastUpdatePositionTime;

	 float MoveSpeed;
};
