// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utilities/FGameStats.h"
#include "Tile.generated.h"

const int NUMBER_OF_TILE_TYPES = 6;
const int INIT_DEFAULT_TILE_VALUE = 100;

class AGrid;
class UBaseEvent;

/**
 * A Tile object is a representation of an entity that exist on a Grid.
 * It uses a limited number of grid moves per turn.
 */
UCLASS()
class PROJECTODIMH_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();
    
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    
    /** Return the value of the tile */
    const uint32 GetTileValue() const;
    
    /** Start the destroy process for Tile objects */
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    
    /** An event when the tile breaks */
    UFUNCTION(BlueprintNativeEvent)
    void OnTileBreak();
    
    /** Set the tile type */
    UFUNCTION(BlueprintNativeEvent)
    void SetTileType(const int Type);
    
    /** Load the tile sprite based on its ID_Type. Function is implemented in blueprint */
    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
    void LoadTileSprite();
    
    UFUNCTION(BlueprintPure)
    static FVector2D GetSourceSize(UPaperSprite* Sprite);
    
    /** The enumeration of a tile type are defined in blueprint */
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn="true"))
    int ID_Type;
    
    UPROPERTY(BlueprintReadWrite)
    FVector2D OldLocation;
    
    UPROPERTY(BlueprintReadWrite)
    FVector2D SpriteSize;
    
    void SetPlayerControlled(const bool bPlayerControlled = true);
    const bool IsControlledByPlayer() const;
    
    UFUNCTION(BlueprintImplementableEvent, BlueprintPure)
    const bool DoesLogic() const;
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
private:
    /** The value of this tile that will be tallied up into a total score when this tile is part of a match */
    UPROPERTY(EditDefaultsOnly)
    uint32 Value;
    
    
};
