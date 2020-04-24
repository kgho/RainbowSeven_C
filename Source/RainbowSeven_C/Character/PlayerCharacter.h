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

protected:
	UPROPERTY(EditAnywhere)
		USpringArmComponent* CameraSpringArm;

	UPROPERTY(EditAnywhere)
		UCameraComponent* FollowCamera;
};
