// Author : Kgho	Github : https://github.com/kgho

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterEntity.generated.h"

class ACombatGameMode;
/**
 * KBE角色类实体对应的UE4角色的基类, 储存实体id, 实体实例, 移动数据, 动作数据, 其派生类实现具体的移动同步逻辑
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

	// 通过血量控制死亡动画播放
	UPROPERTY(BlueprintReadOnly)
		int32 HP;

protected:

	//目标位置
	FVector TargetPosition;

	//目标旋转
	FRotator TargetRotator;

	//上一次更新位置的时间
	float LastUpdatePositionTime;

	 float MoveSpeed;
};
