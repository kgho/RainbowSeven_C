// Author : Kgho	Github : https://github.com/kgho


#include "DefaultCharacter.h"
// Sets default values
ADefaultCharacter::ADefaultCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to  improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}
// Called when the game starts or when spawned
void ADefaultCharacter::BeginPlay()
{
	Super::BeginPlay();

}
// Called every frame
void ADefaultCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
// Called to bind functionality to input
void ADefaultCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
