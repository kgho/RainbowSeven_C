// Author : Kgho	Github : https://github.com/kgho


#include "PlayerCharacter.h"
#include "Controller/CombatController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/KBEngine.h"
#include "Scripts/RSEventData.h"
#include "GameMode/CombatGameMode.h"
#include "UI/CombatWidget.h"

APlayerCharacter::APlayerCharacter()
{
	TurnRate = 30.f;
	LookUpRate = 3.f;

	// 跟随控制器旋转的设置，character只跟随controller 的 yaw 旋转
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// 设置模型位置
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
	// 取消手臂遮挡
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

	PlayerInputComponent->BindAction("ScoreToggle", IE_Pressed, this, &APlayerCharacter::ShowCanvasPanelScoreboard);
	PlayerInputComponent->BindAction("ScoreToggle", IE_Released, this, &APlayerCharacter::HideCanvasPanelScoreboard);
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//获取动作蓝图参数
	AnimSpeed = GetVelocity().Size();
	AnimIsInAir = GetMovementComponent()->IsFalling();

	//获取移动角度
	float PreDir = GetVelocity().ToOrientationRotator().Yaw - GetActorRotation().Yaw;

	if (PreDir > 180.f)
		PreDir -= 360.f;
	if (PreDir < -180.f)
		PreDir += 360.f;

	//速度太小, 移动角度为0
	if (AnimSpeed < 5.f)
		AnimDirection = 0.f;
	else
		AnimDirection = PreDir;
}

void APlayerCharacter::Destroyed()
{
	Super::Destroyed();

	//停止定时器
	GetWorld()->GetTimerManager().ClearTimer(AnimUpdateHandle);
}

void APlayerCharacter::SetBaseHP(int32 InBaseHP)
{
	BaseHP = InBaseHP;
}

void APlayerCharacter::SetHP(int32 InHP)
{
	if (InHP == 0)
	{
		// 死亡,目前还没有观战功能，死亡后切换到UI输入模式
		CombatController->SwitchInputMode(true);
	}

	// 新血值不为0，且比旧血值小，并且不是第一次设置的基础血值，说明在掉血
	if (InHP > 0 && InHP < HP && InHP != BaseHP)
	{
		//播放受击动画
	}

	//保存
	HP = InHP;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 修改输入模式
	CombatController->SwitchInputMode(false);

	//启动更新动作定时器,每0.5秒运行一次，循环true，延时0.5s运行
	GetWorld()->GetTimerManager().SetTimer(AnimUpdateHandle, this, &APlayerCharacter::AnimUpdate, 0.5f, true, 0.5f);
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

void APlayerCharacter::AnimUpdate()
{
	UKBEventData_AnimUpdate* EventData = NewObject<UKBEventData_AnimUpdate>();
	EventData->Speed = AnimSpeed;
	EventData->Direction = AnimDirection;
	KBENGINE_EVENT_FIRE("AnimUpdate", EventData);
}

void APlayerCharacter::ShowCanvasPanelScoreboard()
{
	CombatWidget->ToggleCanvasPanelScoreboard(true);
}

void APlayerCharacter::HideCanvasPanelScoreboard()
{
	CombatWidget->ToggleCanvasPanelScoreboard(false);
}



