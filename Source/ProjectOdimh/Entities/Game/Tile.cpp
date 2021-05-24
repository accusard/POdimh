// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "Tile.h"
#include "PaperSprite.h"
#include "ProjectOdimh.h"
#include "Engine/World.h"
#include "Sound/SoundCue.h"
#include "UObject/ConstructorHelpers.h"
#include "Events/BaseEvent.h"
#include "Entities/Game/Grid.h"
#include "Entities/Game/Match3GameMode.h"
#include "Entities/Controllers/Player/GridPlayerController.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    Value = INIT_DEFAULT_TILE_VALUE;

}

const uint32 ATile::GetTileValue() const
{
    return Value;
}

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
    
    if(EndPlayReason == EEndPlayReason::Destroyed)
    {
        OnTileBreak();
    }
}

void ATile::OnTileBreak_Implementation()
{
    
}

void ATile::SetTileType_Implementation(const int Type)
{
    ID_Type = Type;
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
    
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FVector2D ATile::GetSourceSize(UPaperSprite* Sprite)
{
    return Sprite->GetSourceSize();
}

