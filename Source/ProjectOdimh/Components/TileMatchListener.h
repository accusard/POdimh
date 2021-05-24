// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/EventListener.h"
#include "TileMatchListener.generated.h"

class UBaseEvent;

/**
 * DEPRECATED
 * The component use to respond to delegate broadcasts. Respond to a tile match event and handle the event
 * based on the type and number of matches
 */

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTODIMH_API UTileMatchListener : public UEventListener
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTileMatchListener();
    
    const int GetLastTileMatchTotal() const;
    
    /** A tile match have been made. Tile match logic will be handled here. */
    UFUNCTION()
    void HandleMatch(const int TypeType, const int NumTilesMatching, const int NumTilesNeeded);
    

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
private:
    /** The total quantity of the last matching tiles */
    int LastTileMatchTotal;
};
