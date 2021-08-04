// Copyright 2017-2019 Vanny Sou. All Rights Reserved.


#include "RelayLine.h"
#include "POdimhGameInstance.h"
#include "Entities/Game/Grid.h"

// Sets default values
ARelayLine::ARelayLine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ARelayLine::NotifySave(USaveGame* Data)
{
    if(UPOdimhSaveGame* POdimhData = Cast<UPOdimhSaveGame>(Data))
    {
        for(const FCustomIntData& BPData : OnSaveFromBlueprint())
        {
            POdimhData->CustomInt.Add(*BPData.Id, BPData.Value);
        }
        
        POdimhData->CustomIntPoint.Add(TEXT("LineCoords.Start"), LineCoords.Start);
        POdimhData->CustomIntPoint.Add(TEXT("LineCoords.End"), LineCoords.End);
    }
}

const bool ARelayLine::NotifyLoad(USaveGame* Data)
{
    if(UPOdimhSaveGame* POdimhData = Cast<UPOdimhSaveGame>(Data))
    {
        LineCoords.Start = POdimhData->CustomIntPoint[TEXT("LineCoords.Start")];
        LineCoords.End = POdimhData->CustomIntPoint[TEXT("LineCoords.End")];
        
        TArray<FCustomIntData> CustomDataArray;
        
        for(const TPair<FString, int>& Elem : POdimhData->CustomInt)
        {
            FCustomIntData Loaded;
            Loaded.Id = *Elem.Key;
            Loaded.Value = Elem.Value;
            
            CustomDataArray.Add(Loaded);
        }
        return OnLoadFromBlueprint(CustomDataArray);
    }
    
    
    return false;
}

// Called when the game starts or when spawned
void ARelayLine::BeginPlay()
{
	Super::BeginPlay();
	
    Cast<UPOdimhGameInstance>(GetGameInstance())->EventManager->OnActorEvent.AddDynamic(this, &ARelayLine::Init);
    Cast<UPOdimhGameInstance>(GetGameInstance())->EventManager->OnActorEvent.AddDynamic(this, &ARelayLine::Receive);
}

TArray<ATile*> ARelayLine::GetUnusedTiles(AGrid* Grid)
{
    TArray<ATile*> UnusedTiles;
    for(FIntPoint Coord : ReservedGridCoords)
    {
        if(ATile* Tile = Grid->GetTile(Coord))
            if(Tile->GetIdString() == "Reserved")
                UnusedTiles.Add(Tile);
    }
    
    return UnusedTiles;
}

void ARelayLine::Init_Implementation(AActor* Actor, UBaseEvent* EvtPtr)
{
    EvtPtr->Manager->OnActorEvent.RemoveDynamic(this, &ARelayLine::Init);
    EvtPtr->Manager->OnActorEvent.Broadcast(this, EvtPtr);
}
