// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "TileMatchListener.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "POdimhGameInstance.h"
#include "Gametypes.h"
#include "Events/GridEvent.h"

#if !UE_BUILD_SHIPPING
#include "POdimhGameInstance.h"
#endif


// Sets default values for this component's properties
UTileMatchListener::UTileMatchListener()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

    LastTileMatchTotal = 0;
}


// Called when the game starts
void UTileMatchListener::BeginPlay()
{
	Super::BeginPlay();
//    if(UPOdimhGameInstance* GameInstance = Cast<UPOdimhGameInstance>(GetOwner()->GetGameInstance()))
//    {
//        GameInstance->EventManager->OnTileMatch.AddUniqueDynamic(this, &UTileMatchListener::HandleMatch);
//    }
}

const int UTileMatchListener::GetLastTileMatchTotal() const
{
    return LastTileMatchTotal;
}

void UTileMatchListener::HandleMatch(const int TypeType, const int NumTilesMatching, const int NumTilesNeeded)
{
#if !UE_BUILD_SHIPPING
    APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    Controller->ClientMessage("Received broadcast to HandleMatch()..");
#endif
    LastTileMatchTotal = NumTilesMatching;
    
    if(UPOdimhGameInstance* GameInstance = Cast<UPOdimhGameInstance>(GetOwner()->GetGameInstance()))
    {
        if(NumTilesMatching >= NumTilesNeeded)
        {
            // TODO: tile match logic
#if !UE_BUILD_SHIPPING
            Controller->ClientMessage(FString::Printf(TEXT("A successful match of %i have been made!"), NumTilesMatching));
#endif
        }

    }
}

