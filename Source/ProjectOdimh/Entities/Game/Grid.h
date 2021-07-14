// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ClassInterface/DataSaveInterface.h"

#include "Grid.generated.h"

class ATile;
class USoundCue;

USTRUCT()
struct FTileCount
{
    GENERATED_USTRUCT_BODY()
    
    UPROPERTY()
    int Type = -1;
    
    UPROPERTY()
    int TotalNum = 0;
};

USTRUCT(BlueprintType)
struct FGridSpawningParameters
{
    GENERATED_USTRUCT_BODY()
    
    UPROPERTY(BlueprintReadOnly)
    bool bRandomTileType;
    
    UPROPERTY(BlueprintReadOnly)
    bool bLoadSprites;
    
    UPROPERTY(BlueprintReadOnly)
    FString SaveSlotName;
    
    FGridSpawningParameters()
    {
        bRandomTileType = true;
        bLoadSprites = true;
    }
};
/**
 * The grid contain information that determines the spawning position of each Tile objects, and events that
 * trigger when certain conditions are met.
 */
UCLASS()
class PROJECTODIMH_API AGrid : public APawn, public IDataSaveInterface
{
	GENERATED_BODY()
	
public:
    friend class UGridEvent;
    
	// Sets default values for this actor's properties
	AGrid();
    
    // DataSave interface
    virtual void NotifySave(USaveGame* Data) override;
    virtual const bool NotifyLoad(USaveGame* Data) override;
    
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    const FVector2D& GetGridLocation(const FVector& Location);
    const FVector2D& GetGridLocation(ATile* Tile);
    const FVector2D GetGridLocation(const uint32 TileIndex);
    
    /** Collect data on the number of type occurences that is currently on the grid */
    const TArray<FTileCount> TallyAllTileTypes();
    
    /** Find the number of occurences based on a tile type */
    UFUNCTION(BlueprintCallable)
    const int GetNumOfOccurences(const int Type);
    
    /** Check the grid if there are available matching tiles */
    UFUNCTION(BlueprintCallable)
    const bool MatchingTilesAvailable(int NumOfTileTypes);
    
    /** Score is calculated based on number of tiles, the tile value and a multiplier */
    UFUNCTION(BlueprintCallable)
    const int32 CalculateTileValue(const int NumOfMatchingTiles, const int TileValue, const int Multiplier) const;
    
    const bool HasTilePositionChanged(ATile* Tile);
    
    void NotifyGridStateChanged();
    
    UFUNCTION()
    void CheckState(AActor* Tile);
    
    UFUNCTION()
    void SetOldLocation(AActor* Tile);
    
    /** Determines the distance between a Tile object and another location */
    const float GetDistanceBetween(ATile* Tile, FVector2D OtherPosition);
    
    /** Get the distance between two Tile objects. */
    const float GetDistanceBetween(ATile* TileA, ATile* TileB);
    
    UFUNCTION(BlueprintCallable)
    void OnInitialTilesSpawned(TArray<ATile*> NonMatchTiles);
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    USoundCue* StateChangeCue;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    USoundCue* TileMatchCue;
    
    /** Blueprint Events */
public:
    /** Get the value of GridSize that was assigned in blueprint */
    UFUNCTION(BlueprintImplementableEvent)
    const float GetGridSize() const;
    
    UFUNCTION(BlueprintImplementableEvent)
    const bool IsTilesBursting() const;
    
    UFUNCTION(BlueprintImplementableEvent)
    const bool TilesFinishedFilling() const;
    
    UFUNCTION(BlueprintImplementableEvent)
    const bool IsPickState() const;
    
    /** Return TileList after tile data has been copied from blueprint */
    UFUNCTION(BlueprintImplementableEvent)
    TArray<ATile*> UpdateTileList();
    
    void NewGrid();
    
    UFUNCTION(BlueprintImplementableEvent)
    void InitTiles(const FGridSpawningParameters& Param);
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
    /** Call the blueprint library function GetGridFromLocation to get the grid coordinates by using a Vector location
     * and set it to this object's member data - GridLocation */
    UFUNCTION(BlueprintImplementableEvent)
    void OnRetreiveGridLocation(const FVector& Location);
    
    /** Spawn a tile on the grid based on a transform and tile type. Tile type of -1 is a random spawn. */
    UFUNCTION(BlueprintCallable)
    ATile* SpawnTile(TSubclassOf<ATile> Class, const FTransform& Transform, const int Type = -1);
    
    /** Spawn an actor directly to grid. Only possible if that grid's space is empty. Can notify GameMode of a grid state change after spawning. */
    UFUNCTION(BlueprintNativeEvent)
    void SpawnTileToGrid(ATile* Tile, const bool bNotifyStateChange);
    
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, DisplayName="BurstEnd")
    void OnEventBurstEnd(AMatch3GameMode* Mode);
    
    UFUNCTION(BlueprintCallable)
    void HandleTilesSwapped(AController* GridController, ATile* DynamicTile, ATile* StaticTile);
    
    /** The arrays of gems that was retrieved from blueprint */
    UPROPERTY(BlueprintReadWrite)
    TArray<ATile*> TileList;
    
    /** The grid coordinates that was last retrieved from blueprint */
    UPROPERTY(BlueprintReadWrite)
    FVector2D GridLocation;
    
    /** Tracks a list of tile types to spawn next */
    UPROPERTY(BlueprintReadWrite)
    TArray<int> NextTileToSpawn;
    
    /** The required number of consecutive row or column for the game to consider it a successful tile match */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tiles")
    int TilesNeededForMatch;
    
    UPROPERTY(BlueprintReadWrite)
    uint8 bGridStateChanged : 1;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 SizeX;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 SizeY;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tiles")
    uint8 bSaveTerminalCoords : 1;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tiles")
    uint8 bDefaultTerminalCoordOnBeginPlay :1 ;
    
private:
    /** A state in which there are no matching tiles (2 or less occurences) available */
    uint8 bNoMatchingTiles : 1;
    
    


    
    
    
    

};
