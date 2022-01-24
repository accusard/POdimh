// Copyright 2022 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "Data/FGameStats.h"
#include "Points.generated.h"

const uint32 DEFAULT_MAX_POINTS = 75000;

/**
 *  Game progression using points threshold
 */
UCLASS()
class PROJECTODIMH_API APoints : public AInfo
{
	GENERATED_BODY()
	
public:
    UFUNCTION()
    void NotifyPointsUp(const uint32 Value);
    
    UFUNCTION()
    void NotifyPointsThreshold();
    
    UFUNCTION(BlueprintCallable)
    void Add(const int32 Points, const bool bNotifyPointsUp = true);
    
    void Set(const uint32 Points);
    
    UFUNCTION(BlueprintPure)
    const int32 GetTotalPoints() const;
    
    void SetThreshold(const uint32 Value);
    
    UFUNCTION(BlueprintPure)
    const int32 GetThreshold() const;
    
    UFUNCTION(BlueprintPure)
    const int32 GetDeltaPoints() const;
    
protected:
    UPROPERTY()
    FGameStats Points = FGameStats(0, DEFAULT_MAX_POINTS);
};
