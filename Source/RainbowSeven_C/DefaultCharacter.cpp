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

	if (!IsSinglePlayer) {
		LastUpdatePositionTime = GetWorld()->TimeSeconds;

		//如果不是玩家&&并且GameMode就绪
		if (!IsPlayer && PlayGameMode)
		{
			PlayGameMode->RemoteCharacters.Add(EntityId, this);
		}

		// 由于UE4可视化实体创建要晚于KBE的插件的逻辑实体，而KBE插件实体在场景中的对象生成前可能已经触发了一些属性设置事件
		 // 因此 需要在BeginPlay中再次触发， 例如：血量速度属性值
		AccountInst->callPropertysSetMethods();
	}
}
// Called every frame
void ADefaultCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsSinglePlayer) {
		if (!IsPlayer)
		{
			//旋转平滑
			FRotator CurrentRotator = FMath::RInterpTo(GetActorRotation(), TargetRotator, DeltaTime, 8.0f);
			FaceRotation(CurrentRotator, DeltaTime);
			//位置平滑
			FVector CurrentPosition = GetActorLocation();
			FVector MoveDirection = TargetPosition - CurrentPosition;
			float DeltaDistance = DeltaTime * MoveSpeed;
			float Distance = MoveDirection.Size();
			//如果距离太多或太小，直接设置位置
			if (Distance > 100.f || Distance < DeltaDistance)
			{
				SetActorLocation(TargetPosition);
			}
			else
			{
				//移动过去
				MoveDirection.Normalize();
				SetActorLocation(CurrentPosition + (MoveDirection * DeltaTime));
			}
		}
	}
}
// Called to bind functionality to input
void ADefaultCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

//被销毁后从列表移除
void ADefaultCharacter::Destroyed()
{
	Super::Destroy();
	if (!IsPlayer && PlayGameMode)
	{
		PlayGameMode->RemoteCharacters.Remove(EntityId);
	}
}

void ADefaultCharacter::SetTargetPosition(FVector InPos)
{
	TargetPosition = InPos;
	//获取上次更新到本次更新的时间间隔
	float UpdatePositionSpaceTime = GetWorld()->TimeSeconds - LastUpdatePositionTime;
	//保存本次更新时间
	LastUpdatePositionTime = GetWorld()->TimeSeconds;
	//获取需要移动的距离
	float Distance = FVector::Dist(TargetPosition, GetActorLocation());
	//计算平均速度
	MoveSpeed = Distance / UpdatePositionSpaceTime;
}

void ADefaultCharacter::SetTargetRotator(FRotator InRot)
{
	TargetRotator = InRot;
}
