// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayGameModeBase.h"
#include "DefaultCharacter.h"
#include "Engine/KBEngine.h"
#include "Engine//Entity.h"
#include "Scripts/Account.h"
#include "Kismet/GameplayStatics.h"
void APlayGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	//Login关卡将输入模式设为了仅UI，跳转到Play关卡修改输入模式
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->bShowMouseCursor = false;
	FInputModeGameOnly InputMode;
	InputMode.SetConsumeCaptureMouseDown(false);
	PlayerController->SetInputMode(InputMode);
	//客户端创建cell实体第一次进入房间(客户端创建出实体后直接调用事件)
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onEnterWorld, OnEnterWorld);
	//客户端销毁cell实体离开房间(销毁)
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLeaveWorld, OnLeaveWorld);
	//已经创建的实体跳转场景, 进入新房间
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onEnterSpace, OnEnterSpace);
	//已经创建的实体跳转场景, 离开原房间
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLeaveSpace, OnLeaveSpace);

	//设置位置, 实体进入房间后调用更新状态变量时调用, 可以看做只调用一次
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::set_position, SetPosition);
	//设置旋转, 实体进入房间后调用更新状态变量时调用, 可以看做只调用一次
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::set_direction, SetDirection);
	//实时更新位置旋转, 频率可以修改kbengine.xml文件的gameUpdateHertz来设置
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::updatePosition, UpdatePosition);

	// 如果已经有被创建的实体，说明在上一个场景未来得及跳转之前就已经通知创建了，但由于World场景并没有来得及创建，这部分实体进入世界事件已经漏掉
	// 此时需要再次触发OnEnterWorld，让表现层能够在游戏场景中创建出所有的实体
	KBEngine::KBEngineApp::ENTITIES_MAP& EntitiesMap = KBEngine::KBEngineApp::getSingleton().entities();
	//遍历当前客户端所有存在的实体
	for (auto& EntityItem : EntitiesMap)
	{
		KBEngine::Entity* EntityInst = EntityItem.Value;
		//给每个实体创建一个UKBEventData_onEnterWorld实例
		UKBEventData_onEnterWorld* EventData = NewObject<UKBEventData_onEnterWorld>();
		EventData->entityID = EntityInst->id();
		EventData->spaceID = KBEngine::KBEngineApp::getSingleton().spaceID();
		KBPos2UE4Pos(EventData->position, EntityInst->position);
		EventData->direction = EntityInst->direction;
		EventData->moveSpeed = EntityInst->velocity();
		EventData->isOnGround = EntityInst->isOnGround();
		EventData->isPlayer = EntityInst->isPlayer();
		EventData->entityClassName = EntityInst->className();
		EventData->res = TEXT("");
		KBENGINE_EVENT_FIRE(KBEngine::KBEventTypes::onEnterWorld, EventData);
	}
}
//获取实体数据生成角色
void APlayGameModeBase::OnEnterWorld(const UKBEventData* EventData)
{
	//强转 EventData 到 UKBEventData_onEnterWorld 类型获取实体数据
	const UKBEventData_onEnterWorld* ServerData = Cast<  UKBEventData_onEnterWorld>(EventData);
	//通过 实体ID 获取 实体,通过该实体获取其它数据（如HP）
	KBEngine::Entity* EntityInst = *KBEngine::KBEngineApp::getSingleton().entities().Find(ServerData->entityID);
	//是否是玩家
	if (ServerData->isPlayer)
	{
		KBEngine::Account* AccountInst = static_cast<KBEngine::Account*>(EntityInst);
		FTransform SpawnTransform(PlayerSpawnPos);
		//创建角色但不激活生命周期
		PlayerCharacter = Cast<ADefaultCharacter>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, PlayerCharacterClass, SpawnTransform));
		if (PlayerCharacter)
		{
			//给角色实体 赋值 实体的数据
			PlayerCharacter->EntityId = ServerData->entityID;
			PlayerCharacter->AccountInst = AccountInst;
			PlayerCharacter->PlayGameMode = this;
			PlayerCharacter->IsPlayer = ServerData->isPlayer;
			//激活角色
			UGameplayStatics::FinishSpawningActor(PlayerCharacter, SpawnTransform);
			//将角色绑定到Controller
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			PlayerController->Possess(PlayerCharacter);
		}
	}
	else
	{
		//如果进入的实体不是玩家
		//强转为Account
		KBEngine::Account* AccountInst = static_cast<KBEngine::Account*>(EntityInst);
		FRotator SpawnRotator(0.f, 0.f, 0.f);
		KBDir2UE4Dir(SpawnRotator, ServerData->direction);
		FTransform SpawnTransform(SpawnRotator, ServerData->position);
		//生成对象
		ADefaultCharacter* RemoteCharacter = Cast<ADefaultCharacter>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, RemoteCharacterClass, SpawnTransform));
		if (RemoteCharacter)
		{
			//给角色实体 赋值 实体的数据
			RemoteCharacter->EntityId = ServerData->entityID;
			RemoteCharacter->AccountInst = AccountInst;
			RemoteCharacter->PlayGameMode = this;
			RemoteCharacter->IsPlayer = ServerData->isPlayer;
			//激活角色
			UGameplayStatics::FinishSpawningActor(RemoteCharacter, SpawnTransform);
		}
	}
}

void APlayGameModeBase::OnLeaveWorld(const UKBEventData* EventData)
{
	const UKBEventData_onLeaveWorld* ServerData = Cast<UKBEventData_onLeaveWorld>(EventData);
	if (ServerData->isPlayer)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		PlayerController->UnPossess();
		GetWorld()->DestroyActor(PlayerCharacter);
		PlayerCharacter = NULL;
	}
	else
	{
		if (RemoteCharacters.Contains(ServerData->entityID))
		{
			GetWorld()->DestroyActor(*RemoteCharacters.Find(ServerData->entityID));
		}
	}
}

void APlayGameModeBase::OnEnterSpace(const UKBEventData* EventData)
{
}

void APlayGameModeBase::OnLeaveSpace(const UKBEventData* EventData)
{
}

void APlayGameModeBase::SetPosition(const UKBEventData* EventData)
{
	const  UKBEventData_set_position* ServerData = Cast<UKBEventData_set_position>(EventData);
	if (RemoteCharacters.Contains(ServerData->entityID))
	{
		ADefaultCharacter* RemoteCharacter = *RemoteCharacters.Find(ServerData->entityID);
		RemoteCharacter->SetActorLocation(ServerData->position);
		RemoteCharacter->SetTargetPosition(ServerData->position);
	}
}

void APlayGameModeBase::SetDirection(const UKBEventData* EventData)
{
	const  UKBEventData_set_direction* ServerData = Cast<UKBEventData_set_direction>(EventData);
	if (RemoteCharacters.Contains(ServerData->entityID))
	{
		ADefaultCharacter* RemoteCharacter = *RemoteCharacters.Find(ServerData->entityID);
		RemoteCharacter->SetActorRotation(ServerData->direction);
		RemoteCharacter->SetTargetRotator(ServerData->direction);
	}
}

void APlayGameModeBase::UpdatePosition(const UKBEventData* EventData)
{
	const  UKBEventData_updatePosition* ServerData = Cast<UKBEventData_updatePosition>(EventData);
	if (RemoteCharacters.Contains(ServerData->entityID))
	{
		ADefaultCharacter* RemoteCharacter = *RemoteCharacters.Find(ServerData->entityID);
		//RemoteCharacter->SetActorLocation(ServerData->position);
		//RemoteCharacter->SetActorRotation(ServerData->direction);
		RemoteCharacter->SetTargetPosition(ServerData->position);
		RemoteCharacter->SetTargetRotator(ServerData->direction);
	}
}

