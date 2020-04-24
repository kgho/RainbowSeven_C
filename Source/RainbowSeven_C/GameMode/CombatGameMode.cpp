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
	// ��ʱ������Ҫ�ٴδ���һ��onEnterWorld���ñ��ֲ��ܹ�����Ϸ�����д��������е�ʵ��
	// ������������ʵ�壬����onEnterWorld
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

//�ͻ��˴���cellʵ��ʱ, �ᴥ��onEnterWorld����, �Ѹ�ʵ�����ݸ�֪UE4, 
//���ܻ��в���cell��ͼ�ڿͻ����л���ͼǰ�ʹ��ڲ��ҵ�����onEnterWorld����, 
//�����л���ͼ��, �����Ѿ����ڵ�cellʵ��, ��Ҫ�ֶ�����onEnterWorld����,
void ACombatGameMode::OnEnterWorld(const UKBEventData* EventData)
{
	const UKBEventData_onEnterWorld* ServerData = Cast<UKBEventData_onEnterWorld>(EventData);

	DDH::Debug() << "ACombatGameMode::OnEnterWorld--> entityID: " << ServerData->entityID << DDH::Endl();


	//����ʵ��id��ȡʵ���ʵ��
	KBEngine::Entity* EntityInst = *KBEngine::KBEngineApp::getSingleton().entities().Find(ServerData->entityID);
	//��ȡ��ת
	FRotator Rotator(0.f, 0.f, 0.f);
	KBDir2UE4Dir(Rotator, ServerData->direction);
	//������������UE4����
	if (ServerData->isPlayer)
	{
		// ǿתʵ������ΪRole
		KBEngine::Role* RoleInst = static_cast<KBEngine::Role*>(EntityInst);
		FTransform SpawnTransform(Rotator, RoleInst->SpawnPoint);

		// ���б������� 0 ��ʼ����Ա���ͱ�Ŵ� 1 ��ʼ��
		PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, PlayerClassList[RoleInst->RoleType - 1], SpawnTransform));
		if (PlayerCharacter)
		{
			PlayerCharacter->EntityId = ServerData->entityID;
			PlayerCharacter->CombatGameMode = this;
			PlayerCharacter->RoleType = RoleInst->RoleType;
			PlayerCharacter->RoleName = RoleInst->Name;
			PlayerCharacter->IsPlayer = true;

			// ��������ɫ, ��Ҫ�󶨵�Controller
			ACombatController* CombatController = Cast<ACombatController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

			PlayerCharacter->CombatController = CombatController;

			UGameplayStatics::FinishSpawningActor(PlayerCharacter, SpawnTransform);

			CombatController->Possess(PlayerCharacter);
		}
	}
	else
	{
		// ��ȡ����λ��
		FTransform SpawnTransform(Rotator, ServerData->position);

		// Զ�����
		if (ServerData->entityClassName.Equals(FString("Role")))
		{
			// ǿתʵ������ΪExRole
			KBEngine::Role* RoleInst = static_cast<KBEngine::Role*>(EntityInst);

			//����Զ�����
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

	//���������CharacterMap, ˵�����Ǳ������
	if (CharacterMap.Contains(ServerData->entityID))
	{
		ACharacterEntity* CharacterEntity = *CharacterMap.Find(ServerData->entityID);

		//����ʵ��Id��ȡʵ�����
		KBEngine::Entity* EntityInst = *KBEngine::KBEngineApp::getSingleton().entities().Find(ServerData->entityID);

		//Զ�����
		if (EntityInst->className().Equals(FString("Role")))
		{
			//ֱ������Զ�����
			CharacterEntity->Destroy();
		}
	}
}

void ACombatGameMode::SetPosition(const UKBEventData* EventData)
{
	const UKBEventData_set_position* ServerData = Cast<UKBEventData_set_position>(EventData);
	// �Ǳ������
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
