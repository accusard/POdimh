// Copyright 2017-2021 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "Data/FGameStats.h"
#include "PointTracker.generated.h"

const uint32 DEFAULT_MAX_POINTS = 75000;

/**
 *  Track the game's scoring and a point threshold. Mostly used for game progression.
 */
UCLASS()
class PROJECTODIMH_API APointTracker : public AInfo
{
	GENERATED_BODY()
	
public:
    UFUNCTION()
    void NotifyPointsUp(const uint32 Value);
    
    UFUNCTION()
    void NotifyPointsThreshold();
    
    void Add(const uint32 Value, const uint32 Multiplier = 1);
    
    const uint32 GetTotalPoints() const;
    
    void SetThreshold(const uint32 Value);
    
    const uint32 GetThreshold() const;
    
    const uint32 GetDeltaPoints() const;
    
protected:
    UPROPERTY()
    FGameStats Points = FGameStats(0, DEFAULT_MAX_POINTS);
};
