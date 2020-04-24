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

	HP = 100;
}

// Called when the game starts or when spawned
void ACharacterEntity::BeginPlay()
{
	Super::BeginPlay();

	if (!IsPlayer && CombatGameMode)
		CombatGameMode->CharacterMap.Add(EntityId, this);

	//初始数据
	LastUpdatePositionTime = GetWorld()->TimeSeconds;
	LastUpdateAnimTime = GetWorld()->TimeSeconds;

	//刷新一次实体数据到UE4对象
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

	//获取更新时间间隔
	float UpdatePositionSpaceTime = GetWorld()->TimeSeconds - LastUpdatePositionTime;
	//保存当前时间
	LastUpdatePositionTime = GetWorld()->TimeSeconds;
	//获取距离
	float Distance = FVector::Dist(TargetPosition, GetActorLocation());
	//计算出实时速度
	MoveSpeed = Distance / UpdatePositionSpaceTime;
}

void ACharacterEntity::SetTargetRotator(FRotator InRot)
{
	TargetRotator = InRot;
}

void ACharacterEntity::SetTargetAnim(float Speed, float Direction)
{
	//获取插值头尾状态
	TargetSpeed = Speed;
	TargetDirection = Direction;
	LastSpeed = AnimSpeed;
	LastDirection = AnimDirection;

	//获取时间间隔
	UpdateAnimSpaceTime = GetWorld()->TimeSeconds - LastUpdateAnimTime;
	RemainAnimSpaceTime = UpdateAnimSpaceTime;
	//保留上一次更新的时间
	LastUpdateAnimTime = GetWorld()->TimeSeconds;
}
