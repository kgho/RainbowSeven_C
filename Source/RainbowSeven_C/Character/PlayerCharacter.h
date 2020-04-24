// Author : Kgho	Github : https://github.com/kgho

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterEntity.h"
#include "PlayerCharacter.generated.h"

class ACombatController;
class USpringArmComponent;
class UCameraComponent;
/**
 * ������ҽ�ɫ��
 */
UCLASS()
class RAINBOWSEVEN_C_API APlayerCharacter : public ACharacterEntity
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	// ����� Character �� possess �ǻ�õ� controller
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
