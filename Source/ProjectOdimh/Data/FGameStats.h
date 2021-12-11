// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGameStats.generated.h"




/**
 * A data structs that tracks the minimum and maximum value of a GameStat object
 */
USTRUCT(BlueprintType)
struct FGameStats
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere,Category="")
    uint32 Value;

    UPROPERTY()
    uint32 Default;

    // constructors
    FGameStats();
    FGameStats(const uint32 SetMax);
    FGameStats(const uint32 SetMax, const uint32 SetRemaining);
};
