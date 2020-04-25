// Author : Kgho	Github : https://github.com/kgho

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RSGameInstance.generated.h"

/**
 * 保存跨关卡数据
 */
UCLASS()
class RAINBOWSEVEN_C_API URSGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY()
		FText RoomName;

	// 在Menu关卡 KBEngine::Account::OnReqStartGame 收到游戏准备就绪的消息,触发MenuGameMode事件,保存玩家名称
	// 保存该房间内玩家昵称等，Combat关卡显示
	UPROPERTY()
		TArray<FString> BluePlayerNameArr;

	UPROPERTY()
		TArray<FString> RedPlayerNameArr;

	// 服务端需要添加一个 对战数据
// UPROPERTY()
	// TArray<COMBAT_INFO> CombatInfo;*/

	

};
