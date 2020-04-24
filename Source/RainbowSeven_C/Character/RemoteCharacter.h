// Author : Kgho	Github : https://github.com/kgho

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterEntity.h"
#include "RemoteCharacter.generated.h"

/**
 *
 */
UCLASS()
class RAINBOWSEVEN_C_API ARemoteCharacter : public ACharacterEntity
{
	GENERATED_BODY()

public:
	ARemoteCharacter();

	virtual void Tick(float DeltaTime) override;

};
