// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginGameModeBase.h"

void ALoginGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	//注销该对象注册的所有事件
	KBENGINE_DEREGISTER_ALL_EVENT();
}

void ALoginGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	//KB自己的注册事件系统(字符串，方法名）
	KBENGINE_REGISTER_EVENT("OnSay", OnSay);
	KBENGINE_REGISTER_EVENT("OnLoginSucced", OnLoginSucced);
	KBENGINE_REGISTER_EVENT("addSpaceGeometryMapping", AddSpaceGeometryMapping);
}

void ALoginGameModeBase::Say(FString Msg)
{
	UKBEventData_Say* EventData = NewObject<UKBEventData_Say>();
	EventData->Msg = Msg;
	KBENGINE_EVENT_FIRE("Say", EventData);
	//方法的注册在Consumer,代码执行到这后会调用到Consumer.cpp的__init__，的lamada函数
}

