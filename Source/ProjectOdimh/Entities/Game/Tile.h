// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/FGameStats.h"
#include "Tile.generated.h"

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
    void OnTileBurst();
    
    /** Set the tile type */
    UFUNCTION(BlueprintNativeEvent)
    void SetId(const int Type);
    
    /** Load the tile sprite based on its Id. Function is implemented in blueprint */
    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
    void LoadSprite();
    
    UFUNCTION(BlueprintImplementableEvent)
    const FString GetIdString() const;
    
    /** A unique ID for the tile. When testing for matches, use enumeration defined in blueprint */
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn="true"))
    int Id;
    
    UPROPERTY(BlueprintReadWrite)
    FVector2D OldLocation;
    
    UFUNCTION(BlueprintImplementableEvent, BlueprintPure)
    const bool DoesLogic() const;
    
    UFUNCTION(BlueprintImplementableEvent)
    const FVector2D GetCoord() const;
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
private:
    /** Tally up value to total score when this tile is part of a match */
    UPROPERTY(EditDefaultsOnly)
    uint32 Value;
    
    
};
