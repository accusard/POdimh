// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Data/FGameStats.h"
#include "POdimhGameState.generated.h"

const uint32 DEFAULT_TARGET_THRESHOLD = 15;
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
    int32 LifetimeMatchedTiles;
    
    UPROPERTY(BlueprintReadOnly)
    int32 TierLevel = 1;
    
    UPROPERTY(BlueprintReadWrite)
    int32 Multiplier;
    
    UFUNCTION(BlueprintCallable)
    void ResetTierLevel() { TierLevel = 1; }
    
    UPROPERTY(BlueprintReadWrite)
    FGameStats TierThreshold = FGameStats(DEFAULT_TARGET_THRESHOLD, 0);
    
    uint32 ParticipantIndex = 1;
    
    /** Tracks the current score of the game */
    UPROPERTY()
    int32 CurrentScore;
    
    UPROPERTY()
    uint8 bGameHasStarted : 1;
    
    UPROPERTY()
    class UGameEvent* StartState;

};
