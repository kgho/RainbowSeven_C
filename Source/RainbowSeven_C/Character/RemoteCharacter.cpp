// Author : Kgho	Github : https://github.com/kgho


#include "RemoteCharacter.h"

ARemoteCharacter::ARemoteCharacter()
{
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
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
}
