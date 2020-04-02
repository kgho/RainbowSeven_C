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
	// 由于UE4可视化实体创建要晚于KBE的插件的逻辑实体，而KBE插件实体在场景中的对象生成前可能已经触发了一些属性设置事件
	 // 因此 需要在BeginPlay中再次触发， 例如：血量速度属性值
	AccountInst->callPropertysSetMethods();

	//如果不是玩家&&并且GameMode就绪
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

//被销毁后从列表移除
void ADefaultCharacter::Destroyed()
{
	Super::Destroy();
	if (PlayGameMode)
	{
		PlayGameMode->RemoteCharacters.Remove(EntityId);
	}
}
