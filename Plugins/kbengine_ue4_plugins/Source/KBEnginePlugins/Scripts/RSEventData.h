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
		FString Name;
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

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_ReqRoleInfo : public UKBEventData {

	GENERATED_BODY()

public:
	UPROPERTY()
		uint8 RoleType;


};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_OnReqRoleInfo :public UKBEventData
{
	GENERATED_BODY()

public:
	UPROPERTY()
		FROLE_INFO RoleInfo;
};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_ReqUnlockRole :public UKBEventData
{
	GENERATED_BODY()

public:
	UPROPERTY()
		uint8 RoleType;
};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_ReqRoleList :public UKBEventData
{
	GENERATED_BODY()

public:
	UPROPERTY()
		FString AccountName;
};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_OnReqUnlockRole :public UKBEventData
{
	GENERATED_BODY()

public:
	UPROPERTY()
		uint8 Result;

	UPROPERTY()
		uint8 RoleType;
};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_ReqCreateRoom : public UKBEventData {
	GENERATED_BODY()

public:
	UPROPERTY()
		FString RoomName;
};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_ReqEnterRoom : public UKBEventData {
	GENERATED_BODY()

public:
	UPROPERTY()
		uint64 RoomId;
};

USTRUCT()
struct FROOM_INFO
{
	GENERATED_BODY()
public:
	UPROPERTY()
		uint64 RoomId;
	UPROPERTY()
		FString Name;
	void InitData(uint64 InRoomId, const FString& InName)
	{
		RoomId = InRoomId;
		Name = InName;
	}
};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_OnReqRoomList : public UKBEventData {
	GENERATED_BODY()
public:
	UPROPERTY()
		TArray<FROOM_INFO> RoomList;
};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_OnReqCreateRoom : public UKBEventData {
	GENERATED_BODY()
public:
	UPROPERTY()
		FROOM_INFO RoomInfo;
};

USTRUCT()
struct FPLAYER_INFO
{
	GENERATED_BODY()
public:
	UPROPERTY()
		FString Name;
	UPROPERTY()
		uint16 Levle;
	UPROPERTY()
		uint8 State;
	UPROPERTY()
		uint16 Avatar;
	UPROPERTY()
		uint16 Master;

	void InitData(const FString InName, uint16 InLevle, uint8 InState, uint16 InAvatar, uint16 InMaster)
	{
		Name = InName;
		Levle = InLevle;
		State = InState;
		Avatar = InAvatar;
		Master = InMaster;
	}
};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_OnReqEnterRoom : public UKBEventData {
	GENERATED_BODY()
public:
	UPROPERTY()
		TArray<FPLAYER_INFO> PlayerListBlue;

	UPROPERTY()
		TArray<FPLAYER_INFO> PlayerListRed;
};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_ReqChangeState : public UKBEventData {
	GENERATED_BODY()

public:
	// 0：取消准备， 1：准备
	UPROPERTY()
		uint8 State;
};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_OnReqChangeState : public UKBEventData {
	GENERATED_BODY()

public:
	// 0：未准备， 1：已准备
	UPROPERTY()
		uint8 State;
};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_ReqSelectRole : public UKBEventData {
	GENERATED_BODY()

public:
	// 请求选择的干员类型
	UPROPERTY()
		uint8 RoleType;
};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_OnReqSelectRole : public UKBEventData {
	GENERATED_BODY()

public:
	// 消息码
	UPROPERTY()
		uint8 State;

	// 返回成功选中的干员类型
	UPROPERTY()
		uint8 RoleType;
};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_OnAllReady : public UKBEventData {
	GENERATED_BODY()

public:
	// 0：全部准备，1：否 
	UPROPERTY()
		uint8 AllReady;
};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_AnimUpdate : public UKBEventData {
	GENERATED_BODY()
public:
	UPROPERTY()
		float Speed;

	UPROPERTY()
		float Direction;
};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_OnAnimUpdate : public UKBEventData {
	GENERATED_BODY()
public:
	// 哪个实体更新动作
	UPROPERTY()
		int32 EntityId;

	UPROPERTY()
		float Speed;

	UPROPERTY()
		float Direction;
};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_SetBaseHP : public UKBEventData {
	GENERATED_BODY()
public:
	// 哪个实体更新的
	UPROPERTY()
		int32 EntityId;

	UPROPERTY()
		bool IsPlayer;

	UPROPERTY()
		int32 BaseHP;
};

UCLASS()
class KBENGINEPLUGINS_API UKBEventData_SetHP : public UKBEventData {
	GENERATED_BODY()
public:
	// 哪个实体更新的
	UPROPERTY()
		int32 EntityId;

	UPROPERTY()
		bool IsPlayer;

	UPROPERTY()
		int32 HP;
};

/**
 *
 */
UCLASS()
class KBENGINEPLUGINS_API URSEventData : public UObject
{
	GENERATED_BODY()

};
