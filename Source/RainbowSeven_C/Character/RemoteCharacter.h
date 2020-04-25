// Author : Kgho	Github : https://github.com/kgho

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterEntity.h"
#include "RemoteCharacter.generated.h"

class UBoxComponent;

/**
 *
 */
UCLASS()
class RAINBOWSEVEN_C_API ARemoteCharacter : public ACharacterEntity
{
	GENERATED_BODY()

public:
	ARemoteCharacter();

	virtual void Tick(float DeltaTime) override;

public:

	// 判断是否着地碰撞体,跳跃动画不在服务器同步，仅通过角色与地面是否接触来改变isInAir来控制
	// 检测的 Ground 需要勾选 Generate Overlap Event
	UPROPERTY(EditAnywhere)
		UBoxComponent* GroundBox;

protected:

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:

	static FName GroundName;

};
