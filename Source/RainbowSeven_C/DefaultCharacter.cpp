// Author : Kgho	Github : https://github.com/kgho


#include "DefaultCharacter.h"
#include "Scripts/Account.h"
#include "PlayGameModeBase.h"

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
	// ����UE4���ӻ�ʵ�崴��Ҫ����KBE�Ĳ�����߼�ʵ�壬��KBE���ʵ���ڳ����еĶ�������ǰ�����Ѿ�������һЩ���������¼�
	 // ��� ��Ҫ��BeginPlay���ٴδ����� ���磺Ѫ���ٶ�����ֵ
	AccountInst->callPropertysSetMethods();

	//����������&&����GameMode����
	if (!AccountInst->isPlayer() && PlayGameMode)
	{
		PlayGameMode->RemoteCharacters.Add(EntityId, this);
	}
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

//�����ٺ���б��Ƴ�
void ADefaultCharacter::Destroyed()
{
	Super::Destroy();
	if (PlayGameMode)
	{
		PlayGameMode->RemoteCharacters.Remove(EntityId);
	}
}
