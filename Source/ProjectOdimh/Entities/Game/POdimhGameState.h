// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Data/FGameStats.h"
#include "POdimhGameState.generated.h"

const uint32 DEFAULT_HIGH_SCORE = 75000;
const uint32 DEFAULT_NEXT_TIER_LEVEL = 15;

class APointTracker;
class ATier;

/**
 * 
 */
UCLASS()
class PROJECTODIMH_API APOdimhGameState : public AGameState
{
	GENERATED_BODY()
	
public:
    APOdimhGameState();
    
    UPROPERTY(BlueprintReadWrite)
    int32 ScoreMultiplier = 1;
    
    UPROPERTY(BlueprintReadOnly)
    int32 TurnCounter = 1;
    
    UPROPERTY(BlueprintReadWrite)
    int32 AwarenessCounter;
    
    UPROPERTY(BlueprintReadOnly)
    int32 LifetimeMatchedTiles;
    
    uint32 ParticipantIndex = 1;
    
    UPROPERTY()
    uint8 bGameHasStarted : 1;
    
    UPROPERTY()
    class UGameEvent* StartState;

    UPROPERTY()
    APointTracker* Score;
    
    UPROPERTY()
    ATier* TierProgression;
};
