// Author : Kgho	Github : https://github.com/kgho

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterEntity.h"
#include "PlayerCharacter.generated.h"

class ACombatController;
class USpringArmComponent;
class UCameraComponent;
/**
 * 本地玩家角色类
 */
UCLASS()
class RAINBOWSEVEN_C_API APlayerCharacter : public ACharacterEntity
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	// 当这个 Character 被 possess 是会得到 controller
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void Destroyed() override;

	virtual void SetBaseHP(int32 InBaseHP) override;

	virtual void SetHP(int32 InHP) override;

public:
	ACombatController* CombatController;

	UPROPERTY(EditAnywhere)
		float TurnRate;

	UPROPERTY(EditAnywhere)
		float LookUpRate;


protected:
	virtual void BeginPlay() override;

	void DoJump();

	void DoStopJump();

	void MoveForward(float Value);

	void MoveRight(float Value);

	void Turn(float Value);

	void LookUp(float Value);

	// 定时器绑定的方法
	void AnimUpdate();

protected:
	UPROPERTY(EditAnywhere)
		USpringArmComponent* CameraSpringArm;

	UPROPERTY(EditAnywhere)
		UCameraComponent* FollowCamera;

	//更新动作到服务端定时器句柄，在 begin 中启动，在 destroyed 取消
	FTimerHandle AnimUpdateHandle;
};
