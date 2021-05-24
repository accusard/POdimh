// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "Bay.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABay::ABay()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

const int ABay::GetTileMatchType() const
{
    return TileMatchType;
}

// Called when the game starts or when spawned
void ABay::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABay::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABay::SpawnPowerup(UObject* NewPowerup, const FTransform *Transform)
{
    GetWorld()->SpawnActor(NewPowerup->GetClass(), Transform);
}
