// Author : Kgho	Github : https://github.com/kgho

#pragma once

#include "CoreMinimal.h"
#include "Engine/KBEvent.h"
#include "UObject/NoExportTypes.h"
#include "RSEventData.generated.h"

// 干员角色信息结构体
USTRUCT()
struct FROLE_INFO
{
	GENERATED_BODY()

public:

	UPROPERTY()
		uint64 Dbid;

	UPROPERTY()
		uint8 RoleType;

	UPROPERTY()
		uint8 IsLock;

	UPROPERTY()
		uint32 Kill;

	UPROPERTY()
		uint32 Death;

	UPROPERTY()
		uint32 Assist;

	UPROPERTY()
		uint32 Point;

	UPROPERTY()
		uint32 PlayCount;

	void InitData(DBID InDbid, uint8 InRoleType, uint8 InIsLock, uint32 InKill, uint32 InDeath, uint32 InAssist, uint32 InPoint, uint32 InPlayCount)
	{
		Dbid = InDbid;
		RoleType = InRoleType;
		IsLock = InIsLock;
		Kill = InKill;
		Death = InDeath;
		Assist = InAssist;
		Point = InPoint;
		PlayCount = InPlayCount;
	}
};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_OnReqAccountInfo :public UKBEventData
{
	GENERATED_BODY()

public:
	UPROPERTY()
		uint16 Level;
	UPROPERTY()
		uint64 Exp;
	UPROPERTY()
		uint64 Fame;
	UPROPERTY()
		uint64 Coin;
};


//Account的 OnReqRoleList事件的数据类型
UCLASS()
class KBENGINEPLUGINS_API UKBEventData_OnReqRoleList :public UKBEventData
{
	GENERATED_BODY()

public:
	UPROPERTY()
		TArray<FROLE_INFO> RoleList;
};

/**
 *
 */
UCLASS()
class KBENGINEPLUGINS_API URSEventData : public UObject
{
	GENERATED_BODY()

};
