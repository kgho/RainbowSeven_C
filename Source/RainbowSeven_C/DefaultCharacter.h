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
	// µÃÂID
	int32 EntityId;
	KBEngine::Account* AccountInst;
	APlayGameModeBase* PlayGameMode;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
