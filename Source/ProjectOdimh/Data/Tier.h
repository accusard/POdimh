// Copyright 2017-2021 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Data/PointTracker.h"
#include "Tier.generated.h"

/**
 *  A basic level up progression system.
 */
UCLASS()
class PROJECTODIMH_API ATier : public APointTracker
{
	GENERATED_BODY()
    
public:
    void LevelUp(const uint32 SetPointValue, const uint32 SetPointThreshold);
    
    const uint32 GetLevel() const;
    void SetLevel(const uint32 SetLevel);
    void SetLevel(const uint32 SetLevel, const uint32 PointValue, const uint32 Threshold);
    const uint32 GetPointsForNextLevel() const;
    
private:
    uint32 Level = 1;
	
};
