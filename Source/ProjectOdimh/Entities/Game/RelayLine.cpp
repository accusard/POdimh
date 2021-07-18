// Copyright 2017-2019 Vanny Sou. All Rights Reserved.


#include "RelayLine.h"
#include "POdimhGameInstance.h"

// Sets default values
ARelayLine::ARelayLine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARelayLine::BeginPlay()
{
	Super::BeginPlay();
	
    Cast<UPOdimhGameInstance>(GetGameInstance())->EventManager->OnActorEvent.AddDynamic(this, &ARelayLine::InitOnFinished);
}

// Called every frame
void ARelayLine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


