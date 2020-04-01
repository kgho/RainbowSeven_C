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
			//�����ɫ
			UGameplayStatics::FinishSpawningActor(PlayerCharacter, SpawnTransform);
			//����ɫ�󶨵�Controller
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			PlayerController->Possess(PlayerCharacter);
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
}
void APlayGameModeBase::OnEnterSpace(const UKBEventData* EventData)
{
}
void APlayGameModeBase::OnLeaveSpace(const UKBEventData* EventData)
{
}

