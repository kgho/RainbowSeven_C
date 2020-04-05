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

		//����������&&����GameMode����
		if (!IsPlayer && PlayGameMode)
		{
			PlayGameMode->RemoteCharacters.Add(EntityId, this);
		}

		// ����UE4���ӻ�ʵ�崴��Ҫ����KBE�Ĳ�����߼�ʵ�壬��KBE���ʵ���ڳ����еĶ�������ǰ�����Ѿ�������һЩ���������¼�
		 // ��� ��Ҫ��BeginPlay���ٴδ����� ���磺Ѫ���ٶ�����ֵ
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
			//��תƽ��
			FRotator CurrentRotator = FMath::RInterpTo(GetActorRotation(), TargetRotator, DeltaTime, 8.0f);
			FaceRotation(CurrentRotator, DeltaTime);
			//λ��ƽ��
			FVector CurrentPosition = GetActorLocation();
			FVector MoveDirection = TargetPosition - CurrentPosition;
			float DeltaDistance = DeltaTime * MoveSpeed;
			float Distance = MoveDirection.Size();
			//�������̫���̫С��ֱ������λ��
			if (Distance > 100.f || Distance < DeltaDistance)
			{
				SetActorLocation(TargetPosition);
			}
			else
			{
				//�ƶ���ȥ
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

//�����ٺ���б��Ƴ�
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
	//��ȡ�ϴθ��µ����θ��µ�ʱ����
	float UpdatePositionSpaceTime = GetWorld()->TimeSeconds - LastUpdatePositionTime;
	//���汾�θ���ʱ��
	LastUpdatePositionTime = GetWorld()->TimeSeconds;
	//��ȡ��Ҫ�ƶ��ľ���
	float Distance = FVector::Dist(TargetPosition, GetActorLocation());
	//����ƽ���ٶ�
	MoveSpeed = Distance / UpdatePositionSpaceTime;
}

void ADefaultCharacter::SetTargetRotator(FRotator InRot)
{
	TargetRotator = InRot;
}
