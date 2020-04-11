// Author : Kgho	Github : https://github.com/kgho


#include "KBEClient.h"
#include "Engine/KBEMain.h"

// Sets default values
AKBEClient::AKBEClient()
{
	// Set this actor to call Tick() every frame.  You can turn this off to  improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	KBEMain = CreateDefaultSubobject<UKBEMain>(TEXT("KBEMain"));
}

