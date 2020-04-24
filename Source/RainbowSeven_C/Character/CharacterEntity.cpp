// Author : Kgho	Github : https://github.com/kgho


#include "CharacterEntity.h"
#include "GameMode/CombatGameMode.h"
#include "Engine/KBEngine.h"
#include "Engine/Entity.h"

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

	if (!IsPlayer && CombatGameMode)
		CombatGameMode->CharacterMap.Add(EntityId, this);

	//��ʼ����
	LastUpdatePositionTime = GetWorld()->TimeSeconds;

	//ˢ��һ��ʵ�����ݵ�UE4����
	KBEngine::Entity* EntityInst = KBEngine::KBEngineApp::getSingleton().findEntity(EntityId);
	if (EntityInst)
		EntityInst->callPropertysSetMethods();

}

void ACharacterEntity::Destroyed()
{
	Super::Destroyed();

	if (!IsPlayer && CombatGameMode)
		CombatGameMode->CharacterMap.Remove(EntityId);
}

void ACharacterEntity::SetTargetPosition(FVector InPos)
{
	TargetPosition = InPos;

	//��ȡ����ʱ����
	float UpdatePositionSpaceTime = GetWorld()->TimeSeconds - LastUpdatePositionTime;
	//���浱ǰʱ��
	LastUpdatePositionTime = GetWorld()->TimeSeconds;
	//��ȡ����
	float Distance = FVector::Dist(TargetPosition, GetActorLocation());
	//�����ʵʱ�ٶ�
	MoveSpeed = Distance / UpdatePositionSpaceTime;
}

void ACharacterEntity::SetTargetRotator(FRotator InRot)
{
	TargetRotator = InRot;
}
