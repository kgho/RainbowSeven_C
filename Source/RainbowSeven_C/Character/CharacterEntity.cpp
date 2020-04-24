// Author : Kgho	Github : https://github.com/kgho


#include "CharacterEntity.h"

// Sets default values
ACharacterEntity::ACharacterEntity()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACharacterEntity::BeginPlay()
{
	Super::BeginPlay();
	
}

