// Author : Kgho	Github : https://github.com/kgho


#include "CombatGameMode.h"
#include "Engine/KBEngine.h"
#include "Engine/Entity.h"
#include "Scripts/Role.h"
#include "Kismet/GameplayStatics.h"
#include "Character/PlayerCharacter.h"
#include "Controller/CombatController.h"
#include "Scripts/ExCommon.h"
#include "Character/RemoteCharacter.h"

void ACombatGameMode::BeginPlay()
{
	Super::BeginPlay();
	DDH::Debug() << "ACombatGameMode::BeginPlay-->" << DDH::Endl();
	check(KBEngine::KBEngineApp::getSingleton().isInitialized());
	// 此时我们需要再次触发一次onEnterWorld，让表现层能够在游戏场景中创建出所有的实体
	// 遍历场景所有实体，调用onEnterWorld
	KBEngine::KBEngineApp::ENTITIES_MAP& EntitiesMap = KBEngine::KBEngineApp::getSingleton().entities();
	DDH::Debug() << "ACombatGameMode::BeginPlay--> EntitiesMap.Num: " << EntitiesMap.Num() << DDH::Endl();
	for (auto& EntityItem : EntitiesMap)
	{
		KBEngine::Entity* EntityInst = EntityItem.Value;
		UKBEventData_onEnterWorld* EventData = NewObject<UKBEventData_onEnterWorld>();

		DDH::Debug() << "entityClassName: " << EventData->entityClassName << DDH::Endl();
		DDH::Debug() << "entityID: " << EventData->entityID << DDH::Endl();
		DDH::Debug() << "spaceID: " << EventData->spaceID << DDH::Endl();
		DDH::Debug() << "isPlayer: " << EventData->isPlayer << DDH::Endl();

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

void ACombatGameMode::InstallEvent()
{
	Super::InstallEvent();

	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onEnterWorld, OnEnterWorld);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLeaveWorld, OnLeaveWorld);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onEnterSpace, OnEnterSpace);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLeaveSpace, OnLeaveSpace);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::set_position, SetPosition);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::set_direction, SetDirection);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::updatePosition, UpdatePosition);

	KBENGINE_REGISTER_EVENT("OnAnimUpdate", OnAnimUpdate);
	KBENGINE_REGISTER_EVENT("SetBaseHP", SetBaseHP);
	KBENGINE_REGISTER_EVENT("SetHP", SetHP);
}

//客户端创建cell实体时, 会触发onEnterWorld方法, 把该实体数据告知UE4, 
//可能会有部分cell视图在客户端切换地图前就存在并且调用了onEnterWorld方法, 
//所以切换地图后, 对于已经存在的cell实体, 需要手动调用onEnterWorld函数,
void ACombatGameMode::OnEnterWorld(const UKBEventData* EventData)
{
	const UKBEventData_onEnterWorld* ServerData = Cast<UKBEventData_onEnterWorld>(EventData);

	DDH::Debug() << "ACombatGameMode::OnEnterWorld--> entityID: " << ServerData->entityID << DDH::Endl();


	//根据实体id获取实体的实例
	KBEngine::Entity* EntityInst = *KBEngine::KBEngineApp::getSingleton().entities().Find(ServerData->entityID);
	//获取旋转
	FRotator Rotator(0.f, 0.f, 0.f);
	KBDir2UE4Dir(Rotator, ServerData->direction);
	//区分类型生成UE4对象
	if (ServerData->isPlayer)
	{
		// 强转实体类型为Role
		KBEngine::Role* RoleInst = static_cast<KBEngine::Role*>(EntityInst);
		FTransform SpawnTransform(Rotator, RoleInst->SpawnPoint);

		// 类列表索引从 0 开始，干员类型编号从 1 开始。
		PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, PlayerClassList[RoleInst->RoleType - 1], SpawnTransform));
		if (PlayerCharacter)
		{
			PlayerCharacter->EntityId = ServerData->entityID;
			PlayerCharacter->CombatGameMode = this;
			PlayerCharacter->RoleType = RoleInst->RoleType;
			PlayerCharacter->RoleName = RoleInst->Name;
			PlayerCharacter->IsPlayer = true;

			// 创建出角色, 需要绑定到Controller
			ACombatController* CombatController = Cast<ACombatController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

			PlayerCharacter->CombatController = CombatController;

			UGameplayStatics::FinishSpawningActor(PlayerCharacter, SpawnTransform);

			CombatController->Possess(PlayerCharacter);
		}
	}
	else
	{
		// 获取生成位置
		FTransform SpawnTransform(Rotator, ServerData->position);

		// 远程玩家
		if (ServerData->entityClassName.Equals(FString("Role")))
		{
			// 强转实体类型为ExRole
			KBEngine::Role* RoleInst = static_cast<KBEngine::Role*>(EntityInst);

			//生成远程玩家
			ARemoteCharacter* RemoteCharacter = Cast<ARemoteCharacter>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, RemoteClassList[RoleInst->RoleType - 1], SpawnTransform));
			if (RemoteCharacter)
			{
				RemoteCharacter->EntityId = ServerData->entityID;
				RemoteCharacter->CombatGameMode = this;
				RemoteCharacter->RoleType = RoleInst->RoleType;
				RemoteCharacter->RoleName = RoleInst->Name;
				RemoteCharacter->IsPlayer = false;

				UGameplayStatics::FinishSpawningActor(RemoteCharacter, SpawnTransform);
			}
		}
	}
}

void ACombatGameMode::UnInstallEvent()
{
}

void ACombatGameMode::OnLeaveWorld(const UKBEventData* EventData)
{
}

void ACombatGameMode::OnEnterSpace(const UKBEventData* EventData)
{
}

void ACombatGameMode::OnLeaveSpace(const UKBEventData* EventData)
{
	const UKBEventData_onLeaveWorld* ServerData = Cast<UKBEventData_onLeaveWorld>(EventData);

	//如果存在于CharacterMap, 说明不是本地玩家
	if (CharacterMap.Contains(ServerData->entityID))
	{
		ACharacterEntity* CharacterEntity = *CharacterMap.Find(ServerData->entityID);

		//根据实体Id获取实体对象
		KBEngine::Entity* EntityInst = *KBEngine::KBEngineApp::getSingleton().entities().Find(ServerData->entityID);

		//远程玩家
		if (EntityInst->className().Equals(FString("Role")))
		{
			//直接销毁远程玩家
			CharacterEntity->Destroy();
		}
	}
}

void ACombatGameMode::SetPosition(const UKBEventData* EventData)
{
	const UKBEventData_set_position* ServerData = Cast<UKBEventData_set_position>(EventData);
	// 非本地玩家
	if (CharacterMap.Contains(ServerData->entityID))
	{
		ACharacterEntity* CharacterEntity = *CharacterMap.Find(ServerData->entityID);
		CharacterEntity->SetActorLocation(ServerData->position);
		CharacterEntity->SetTargetPosition(ServerData->position);
	}
}

void ACombatGameMode::SetDirection(const UKBEventData* EventData)
{
	const UKBEventData_set_direction* ServerData = Cast<UKBEventData_set_direction>(EventData);

	if (CharacterMap.Contains(ServerData->entityID))
	{
		ACharacterEntity* CharacterEntity = *CharacterMap.Find(ServerData->entityID);
		CharacterEntity->SetActorRotation(ServerData->direction);
		CharacterEntity->SetTargetRotator(ServerData->direction);
	}
}

void ACombatGameMode::UpdatePosition(const UKBEventData* EventData)
{
	const UKBEventData_updatePosition* ServerData = Cast<UKBEventData_updatePosition>(EventData);

	if (CharacterMap.Contains(ServerData->entityID))
	{
		ACharacterEntity* CharacterEntity = *CharacterMap.Find(ServerData->entityID);
		CharacterEntity->SetTargetPosition(ServerData->position);
		CharacterEntity->SetTargetRotator(ServerData->direction);
	}
}

void ACombatGameMode::OnAnimUpdate(const UKBEventData* EventData)
{
}

void ACombatGameMode::SetBaseHP(const UKBEventData* EventData)
{
}

void ACombatGameMode::SetHP(const UKBEventData* EventData)
{
}
