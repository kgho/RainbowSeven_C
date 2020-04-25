// Author : Kgho	Github : https://github.com/kgho


#include "RemoteCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"

FName ARemoteCharacter::GroundName(TEXT("Ground"));

ARemoteCharacter::ARemoteCharacter()
{
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	GroundBox = CreateDefaultSubobject<UBoxComponent>(TEXT("GroundBox"));
	GroundBox->SetupAttachment(RootComponent);
	GroundBox->SetCollisionProfileName(FName("OverlapAll"));

	// 绑定，通过反射触发事件
	FScriptDelegate OverlapBegin;
	OverlapBegin.BindUFunction(this, "OnOverlapBegin");
	GroundBox->OnComponentBeginOverlap.Add(OverlapBegin);

	FScriptDelegate OverlapEnd;
	OverlapEnd.BindUFunction(this, "OnOverlapEnd");
	GroundBox->OnComponentEndOverlap.Add(OverlapEnd);
}

void ARemoteCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//位置更新
	FVector CurrentPosition = GetActorLocation();

	FVector MoveDirection = TargetPosition - CurrentPosition;

	float DeltaSpace = DeltaTime * MoveSpeed;

	float Distance = MoveDirection.Size();

	//距离太大或者太小直接设置到目标位置
	if (Distance > 100.f || Distance < DeltaSpace)
		SetActorLocation(TargetPosition);
	else
	{
		//移动位置
		MoveDirection.Normalize();
		SetActorLocation(CurrentPosition + MoveDirection * DeltaSpace);
	}

	//旋转更新
	FRotator CurrentRotation = FMath::RInterpTo(GetActorRotation(), TargetRotator, DeltaTime, 5.f);
	FaceRotation(CurrentRotation);

	// 更新动画，* 5加快动作的切换
	RemainAnimSpaceTime -= DeltaTime * 5;
	float AnimLerpPercent = FMath::Clamp(RemainAnimSpaceTime / UpdateAnimSpaceTime, 0.f, 1.f);
	AnimSpeed = FMath::Lerp(TargetSpeed, LastSpeed, AnimLerpPercent);
	AnimDirection = FMath::Lerp(TargetDirection, LastDirection, AnimLerpPercent);
}

void ARemoteCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//是否碰到地面
	if (OtherActor->GetFName().IsEqual(GroundName))
	{
		AnimIsInAir = false;
	}
}

void ARemoteCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//是否碰到地面
	if (OtherActor->GetFName().IsEqual(GroundName))
	{
		AnimIsInAir = true;
	}
}
