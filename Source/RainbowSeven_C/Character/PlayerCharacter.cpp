// Author : Kgho	Github : https://github.com/kgho


#include "PlayerCharacter.h"
#include "Controller/CombatController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"

APlayerCharacter::APlayerCharacter()
{
	TurnRate = 30.f;
	LookUpRate = 3.f;

	// �����������ת�����ã�characterֻ����controller �� yaw ��ת
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// ����ģ��λ��
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	CameraSpringArm->SetupAttachment(RootComponent);
	CameraSpringArm->TargetArmLength = 600.0f; // The camera follows at this distance behind the character	
	CameraSpringArm->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	CameraSpringArm->SetRelativeLocation(FVector(0.f, 0.f, 120.f));
	// ȡ���ֱ��ڵ�
	CameraSpringArm->bDoCollisionTest = false;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::DoJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacter::DoStopJump);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//��ȡ������ͼ����
	AnimSpeed = GetVelocity().Size();
	AnimIsInAir = GetMovementComponent()->IsFalling();

	//��ȡ�ƶ��Ƕ�
	float PreDir = GetVelocity().ToOrientationRotator().Yaw - GetActorRotation().Yaw;

	if (PreDir > 180.f)
		PreDir -= 360.f;
	if (PreDir < -180.f)
		PreDir += 360.f;

	//�ٶ�̫С, �ƶ��Ƕ�Ϊ0
	if (AnimSpeed < 5.f)
		AnimDirection = 0.f;
	else
		AnimDirection = PreDir;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// �޸�����ģʽ
	CombatController->SwitchInputMode(false);
}

void APlayerCharacter::DoJump()
{
	Jump();
}

void APlayerCharacter::DoStopJump()
{
	StopJumping();
}

void APlayerCharacter::MoveForward(float Value)
{
	if (Controller != NULL && Value != 0.f)
	{
		const FRotator Rotation = CombatController->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if (Controller != NULL && Value != 0.f)
	{
		const FRotator Rotation = CombatController->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::Turn(float Value)
{
	AddControllerYawInput(Value * TurnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value * LookUpRate * GetWorld()->GetDeltaSeconds());
}


