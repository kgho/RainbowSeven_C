// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginGameModeBase.h"

void ALoginGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	//KB�Լ���ע���¼�ϵͳ(�ַ�������������
	KBENGINE_REGISTER_EVENT("OnSay", OnSay);
	KBENGINE_REGISTER_EVENT("OnLoginSucced", OnLoginSucced);
	KBENGINE_REGISTER_EVENT("addSpaceGeometryMapping", AddSpaceGeometryMapping);
}

void ALoginGameModeBase::Say(FString Msg)
{
	UKBEventData_Say* EventData = NewObject<UKBEventData_Say>();
	EventData->Msg = Msg;
	KBENGINE_EVENT_FIRE("Say", EventData);
	//������ע����Consumer,����ִ�е�������õ�Consumer.cpp��__init__����lamada����
}

