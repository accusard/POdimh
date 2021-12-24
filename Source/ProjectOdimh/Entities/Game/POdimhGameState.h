// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Data/FGameStats.h"
#include "POdimhGameState.generated.h"

const uint32 DEFAULT_TIER_THRESHOLD = 15;

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
    
    APointTracker* GetScore() { return Score; }
    
    ATier* GetScoreTier() { return ScoreTier; }
    
    void AddToScore(const int32 Points, const int32 Multiplier);
    
    const uint32 GetTotalScore() const;
    
    void AddToTierPoints(const uint32 Points);
    
    const uint32 GetTierLevel() const;
    
    UPROPERTY(BlueprintReadWrite)
    int32 ScoreMultiplier = 1;
    
    UPROPERTY(BlueprintReadOnly)
    int32 TurnCounter = 1;
    
    UPROPERTY(BlueprintReadWrite)
    int32 AwarenessCounter;
    
    UPROPERTY(BlueprintReadOnly)
    int32 LifetimeMatchedTiles;
    
    UPROPERTY(BlueprintReadOnly)
    int32 TierLevel = 1;
    
    UFUNCTION(BlueprintCallable)
    void ResetTierLevel() { TierLevel = 1; }
    
    UPROPERTY(BlueprintReadWrite)
    FGameStats TierThreshold = FGameStats(0, DEFAULT_TIER_THRESHOLD);
    
    uint32 ParticipantIndex = 1;
    
    /** Tracks the current score of the game */
    UPROPERTY()
    int32 CurrentScore;
    
    UPROPERTY()
    uint8 bGameHasStarted : 1;
    
    UPROPERTY()
    class UGameEvent* StartState;

private:
    UPROPERTY()
    APointTracker* Score;
    
    UPROPERTY()
    ATier* ScoreTier;
};
