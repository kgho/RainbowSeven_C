// Author : Kgho. Github:https://github.com/kgho

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Scripts/Account.h"
#include "DefaultCharacter.generated.h"
class APlayGameModeBase;
UCLASS()
class RAINBOWSEVEN_C_API ADefaultCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	ADefaultCharacter();

	bool IsPlayer;

	//ʵ��ID
	int32 EntityId;
	KBEngine::Account* AccountInst;
	APlayGameModeBase* PlayGameMode;

	void SetTargetPosition(FVector InPos);

	void SetTargetRotator(FRotator InRot);

	//Ŀ��λ��
	FVector TargetPosition;

	//Ŀ����ת
	FRotator TargetRotator;

	//ƽ���ƶ���ת���ٶ�
	float MoveSpeed;

	//��һ�θ���λ�õ�ʱ��
	float LastUpdatePositionTime;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Destroyed() override;
};
