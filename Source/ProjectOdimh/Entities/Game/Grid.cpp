// Copyright 2017-2019 Vanny Sou. All Rights Reserved.

#include "Grid.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "Events/BaseEvent.h"
#include "ProjectOdimh.h"
#include "Entities/Game/Match3GameMode.h"
#include "Entities/Game/Tile.h"
#include "Entities/States/State.h"
#include "Components/ActionTurnBasedComponent.h"
#include "Components/ActorPickHandlerComponent.h"
#include "POdimhGameInstance.h"
#include "POdimhGameState.h"
#include "POdimhSaveGame.h"
#include "Events/GameEvent.h"
#include "Events/GridEvent.h"
#include "Sound/SoundCue.h"


// Sets default values
AGrid::AGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    TilesNeededForMatch = 3;
    bNoMatchingTiles = false;
    bGridStateChanged = false;

    
//    static ConstructorHelpers::FObjectFinder<USoundCue> DefaultStateChangeCue(TEXT("undefined"));
    
    static ConstructorHelpers::FObjectFinder<USoundCue> DefaultTileMatchCue(TEXT("SoundCue'/Game/The_Future_Is_Now/cues/1_Neutral/UI_Neutral_226_Cue.UI_Neutral_226_Cue'"));
    
//    if(DefaultStateChangeCue.Object)
//        StateChangeCue = DefaultStateChangeCue.Object;
    
    if(DefaultTileMatchCue.Object)
        TileMatchCue = DefaultTileMatchCue.Object;
    
}

void AGrid::NotifySave(USaveGame* SaveData)
{
    if(UPOdimhSaveGame* Data = Cast<UPOdimhSaveGame>(SaveData))
    {
        // save the tile types
        for(ATile* Tile : UpdateTileList())
        {
            if(Tile->DoesLogic())
                Data->Board.NodeLocations.Add(GetGridLocation(Tile));
            
            // for each tile, assign types to save data
            Data->Board.AddTile(Tile->ID_Type);
        }
        TileList.Empty();
    }
}

const bool AGrid::NotifyLoad(USaveGame* LoadData)
{
    bool bSuccess = false;
    
    if(UPOdimhSaveGame* Data = Cast<UPOdimhSaveGame>(LoadData))
    {
        FGridSpawningParameters Params;
        Params.bRandomTileType = false;
        Params.bLoadSprites = true;
        Params.SaveSlotName = CONTINUE_GAME_SLOT;
        
        InitTiles(Params);
        UpdateTileList();
        
        if(ensure(TileList.Num() == Data->Board.GetNumberOfTiles()))
            bSuccess = true;

        TileList.Empty();
    }
    return bSuccess;
}

const FVector2D& AGrid::GetGridLocation(const FVector& Location)
{
    // call the blueprint library function to retrieve the data
    OnRetreiveGridLocation(Location);
    
    return GridLocation;
}

const FVector2D& AGrid::GetGridLocation(ATile* Tile)
{
    return GetGridLocation(Tile->GetActorLocation());
}

const FVector2D AGrid::GetGridLocation(const uint32 TileIndex)
{
    return FVector2D(TileIndex % SizeX, TileIndex / SizeX);
}

const TArray<FTileData> AGrid::CountTileTypes()
{
    TArray<FTileData> GridData;
    
    for(auto* Tile: UpdateTileList())
    {
        if(Tile)
        {
            bool bDataTypeFound = false;
            
            for(FTileData& CurrData : GridData)
            {
                if(CurrData.Type == Tile->ID_Type)
                {
                    CurrData.TotalNum++;
                    bDataTypeFound = true;
                    break;
                }
            }
            
            // create new data only if a certain type doesn't exist
            if(!bDataTypeFound)
            {
                FTileData NewData;
                NewData.Type = Tile->ID_Type;
                NewData.TotalNum++;
                GridData.Add(NewData);
            }
        }
    }
    TileList.Empty();
    return GridData;
}

const int AGrid::GetNumOfOccurences(const int Type)
{
    int Count = 0;
    
    for(const FTileData& CurrTileData : CountTileTypes())
    {
        if(CurrTileData.Type == Type)
        {
            Count = CurrTileData.TotalNum;
            break;
        }
    }
    return Count;
}

const bool AGrid::MatchingTilesAvailable()
{
    for(int type = 0; type < NUMBER_OF_TILE_TYPES; type++ )
    {
        // TODO: note that function GetNumOfOccurences() is calling CountTileTypes() in a loop
        int TileCount = GetNumOfOccurences(type);
        
        // return true if there are available matches
        if(TileCount >= TilesNeededForMatch)
        {
            return true;
        }
    }
    
    return false;
}

const bool AGrid::HasTilePositionChanged(ATile* Tile)
{
    if(Tile)
    {
        const FVector2D TileCurrLocation = GetGridLocation(Tile);
        const FVector2D TileOldLocation = Tile->OldLocation;
        
        if(TileCurrLocation != TileOldLocation)
            return true;
    }
    
    return false;
}

void AGrid::NotifyGridStateChanged()
{
    Cast<UPOdimhGameInstance>(GetGameInstance())->EventManager->NewEvent<UGridEvent>(this, "Grid State Change", true);
    bGridStateChanged = false;
}

void AGrid::CheckState(AActor* Actor)
{
    if(bGridStateChanged || HasTilePositionChanged(Cast<ATile>(Actor)))
        NotifyGridStateChanged();
}

void AGrid::SetOldLocation(AActor* Actor)
{
    if(ATile* Tile = Cast<ATile>(Actor))
        Tile->OldLocation = GetGridLocation(Tile);
}

const float AGrid::GetDistanceBetween(ATile* Tile, FVector2D OtherPosition)
{
    // determine the distance between its current position and its new position
    return FVector2D::Distance(FVector2D(Tile->GetActorLocation()), OtherPosition);
}

const float GetDistanceBetween(ATile* TileA, ATile* TileB)
{
    return FVector::Distance(TileA->GetActorLocation(), TileB->GetActorLocation());
}

const int32 AGrid::CalculateTileValue(const int NumOfMatchingTiles, const int TileValue, const int Multiplier) const
{
    const int TotalScore = NumOfMatchingTiles * TileValue * Multiplier;
    
    return TotalScore;
}

void AGrid::OnEventBurstEnd_Implementation(AMatch3GameMode* Mode)
{
    Mode->ReceiveRequestToEndTurn();
}

void AGrid::HandleTilesSwapped(ATile* DynamicTile, ATile* StaticTile)
{
    
}

// Called when the game starts or when spawned
void AGrid::BeginPlay()
{
	Super::BeginPlay();
    
    Cast<UPOdimhGameInstance>(GetGameInstance())->EventManager->OnActorPicked.AddDynamic(this, &AGrid::SetOldLocation);
    Cast<UPOdimhGameInstance>(GetGameInstance())->EventManager->OnActorReleased.AddDynamic(this, &AGrid::CheckState);
}

void AGrid::NewGrid()
{
    FGridSpawningParameters Params;
    InitTiles(Params);
}

void AGrid::SpawnTileToGrid_Implementation(ATile* Tile, const bool bNotifyStateChange)
{
    if(bNotifyStateChange)
        Cast<UPOdimhGameInstance>(GetGameInstance())->EventManager->NewEvent<UGridEvent>(this, "Grid State Change", true);
}

ATile* AGrid::SpawnTile(TSubclassOf<ATile> BlueprintClass, const FTransform& Transform, const int Type /* = -1 */)
{
    ATile* SpawnedTile = GetWorld()->SpawnActor<ATile>(BlueprintClass, Transform);
    
    if(SpawnedTile) SpawnedTile->SetTileType(Type);

    return SpawnedTile;
}

// Called every frame
void AGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
}

