// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "POdimhGameState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTODIMH_API APOdimhGameState : public AGameState
{
	GENERATED_BODY()
	
public:
    APOdimhGameState();
    
    UPROPERTY(BlueprintReadOnly)
    int32 TurnCounter = 1;
    
    UPROPERTY(BlueprintReadWrite)
    int32 AwarenessCounter;
    
    UPROPERTY(BlueprintReadOnly)
    int32 TotalMatchedTiles;
    
    uint32 ParticipantIndex = 1;
    
    /** Tracks the current score of the game */
    UPROPERTY()
    int32 CurrentScore;
    
    UPROPERTY()
    uint8 bGameHasStarted : 1;
    
    UPROPERTY()
    class UGameEvent* StartState;

};
