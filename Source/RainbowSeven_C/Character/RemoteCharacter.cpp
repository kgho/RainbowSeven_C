// Author : Kgho	Github : https://github.com/kgho


#include "RemoteCharacter.h"

ARemoteCharacter::ARemoteCharacter()
{
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
}

void ARemoteCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//λ�ø���
	FVector CurrentPosition = GetActorLocation();

	FVector MoveDirection = TargetPosition - CurrentPosition;

	float DeltaSpace = DeltaTime * MoveSpeed;

	float Distance = MoveDirection.Size();

	//����̫�����̫Сֱ�����õ�Ŀ��λ��
	if (Distance > 100.f || Distance < DeltaSpace)
		SetActorLocation(TargetPosition);
	else
	{
		//�ƶ�λ��
		MoveDirection.Normalize();
		SetActorLocation(CurrentPosition + MoveDirection * DeltaSpace);
	}

	//��ת����
	FRotator CurrentRotation = FMath::RInterpTo(GetActorRotation(), TargetRotator, DeltaTime, 5.f);
	FaceRotation(CurrentRotation);
}
