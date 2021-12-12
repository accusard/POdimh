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

void ARelayLine::Save(USaveGame* Data)
{
    if(UPOdimhSaveGame* POdimhData = Cast<UPOdimhSaveGame>(Data))
    {
        for(const FCustomIntData& BPData : OnSaveFromBlueprint())
        {
            POdimhData->CustomInt.Add(*BPData.Id, BPData.Value);
        }
        
        POdimhData->CustomIntPoint.Add("LineCoords.Start", LineCoords.Start);
        POdimhData->CustomIntPoint.Add("LineCoords.End", LineCoords.End);
    }
}

const bool ARelayLine::Load(USaveGame* Data)
{
    if(UPOdimhSaveGame* POdimhData = Cast<UPOdimhSaveGame>(Data))
    {
        LineCoords.Start = POdimhData->CustomIntPoint["LineCoords.Start"];
        LineCoords.End = POdimhData->CustomIntPoint["LineCoords.End"];
        
        TArray<FCustomIntData> CustomDataArray;
        
        for(const TPair<FString, int>& Elem : POdimhData->CustomInt)
        {
            FCustomIntData Loaded(*Elem.Key, Elem.Value);
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
	
    UEventManager* EvtMgr = Cast<UPOdimhGameInstance>(GetGameInstance())->EventManager;
    EvtMgr->OnActorEvent.AddDynamic(this, &ARelayLine::Init);
    EvtMgr->OnActorEvent.AddDynamic(this, &ARelayLine::Receive);
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
