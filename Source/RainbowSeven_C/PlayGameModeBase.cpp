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
	//Login�ؿ�������ģʽ��Ϊ�˽�UI����ת��Play�ؿ��޸�����ģʽ
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->bShowMouseCursor = false;
	FInputModeGameOnly InputMode;
	InputMode.SetConsumeCaptureMouseDown(false);
	PlayerController->SetInputMode(InputMode);
	//�ͻ��˴���cellʵ���һ�ν��뷿��(�ͻ��˴�����ʵ���ֱ�ӵ����¼�)
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onEnterWorld, OnEnterWorld);
	//�ͻ�������cellʵ���뿪����(����)
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLeaveWorld, OnLeaveWorld);
	//�Ѿ�������ʵ����ת����, �����·���
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onEnterSpace, OnEnterSpace);
	//�Ѿ�������ʵ����ת����, �뿪ԭ����
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLeaveSpace, OnLeaveSpace);

	//����λ��, ʵ����뷿�����ø���״̬����ʱ����, ���Կ���ֻ����һ��
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::set_position, SetPosition);
	//������ת, ʵ����뷿�����ø���״̬����ʱ����, ���Կ���ֻ����һ��
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::set_direction, SetDirection);
	//ʵʱ����λ����ת, Ƶ�ʿ����޸�kbengine.xml�ļ���gameUpdateHertz������
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::updatePosition, UpdatePosition);

	// ����Ѿ��б�������ʵ�壬˵������һ������δ���ü���ת֮ǰ���Ѿ�֪ͨ�����ˣ�������World������û�����ü��������ⲿ��ʵ����������¼��Ѿ�©��
	// ��ʱ��Ҫ�ٴδ���OnEnterWorld���ñ��ֲ��ܹ�����Ϸ�����д��������е�ʵ��
	KBEngine::KBEngineApp::ENTITIES_MAP& EntitiesMap = KBEngine::KBEngineApp::getSingleton().entities();
	//������ǰ�ͻ������д��ڵ�ʵ��
	for (auto& EntityItem : EntitiesMap)
	{
		KBEngine::Entity* EntityInst = EntityItem.Value;
		//��ÿ��ʵ�崴��һ��UKBEventData_onEnterWorldʵ��
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
//��ȡʵ���������ɽ�ɫ
void APlayGameModeBase::OnEnterWorld(const UKBEventData* EventData)
{
	//ǿת EventData �� UKBEventData_onEnterWorld ���ͻ�ȡʵ������
	const UKBEventData_onEnterWorld* ServerData = Cast<  UKBEventData_onEnterWorld>(EventData);
	//ͨ�� ʵ��ID ��ȡ ʵ��,ͨ����ʵ���ȡ�������ݣ���HP��
	KBEngine::Entity* EntityInst = *KBEngine::KBEngineApp::getSingleton().entities().Find(ServerData->entityID);
	//�Ƿ������
	if (ServerData->isPlayer)
	{
		KBEngine::Account* AccountInst = static_cast<KBEngine::Account*>(EntityInst);
		FTransform SpawnTransform(PlayerSpawnPos);
		//������ɫ����������������
		PlayerCharacter = Cast<ADefaultCharacter>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, PlayerCharacterClass, SpawnTransform));
		if (PlayerCharacter)
		{
			//����ɫʵ�� ��ֵ ʵ�������
			PlayerCharacter->EntityId = ServerData->entityID;
			PlayerCharacter->AccountInst = AccountInst;
			PlayerCharacter->PlayGameMode = this;
			PlayerCharacter->IsPlayer = ServerData->isPlayer;
			//�����ɫ
			UGameplayStatics::FinishSpawningActor(PlayerCharacter, SpawnTransform);
			//����ɫ�󶨵�Controller
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			PlayerController->Possess(PlayerCharacter);
		}
	}
	else
	{
		//��������ʵ�岻�����
		//ǿתΪAccount
		KBEngine::Account* AccountInst = static_cast<KBEngine::Account*>(EntityInst);
		FRotator SpawnRotator(0.f, 0.f, 0.f);
		KBDir2UE4Dir(SpawnRotator, ServerData->direction);
		FTransform SpawnTransform(SpawnRotator, ServerData->position);
		//���ɶ���
		ADefaultCharacter* RemoteCharacter = Cast<ADefaultCharacter>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, RemoteCharacterClass, SpawnTransform));
		if (RemoteCharacter)
		{
			//����ɫʵ�� ��ֵ ʵ�������
			RemoteCharacter->EntityId = ServerData->entityID;
			RemoteCharacter->AccountInst = AccountInst;
			RemoteCharacter->PlayGameMode = this;
			RemoteCharacter->IsPlayer = ServerData->isPlayer;
			//�����ɫ
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

