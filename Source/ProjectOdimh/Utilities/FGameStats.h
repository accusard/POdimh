// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGameStats.generated.h"

const int INIT_HIT_POINTS = 1;


/**
 * A data structs that tracks the minimum and maximum value of a GameStat object
 */
USTRUCT(BlueprintType)
struct FGameStats
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere,Category="")
    uint32 Remaining;

    UPROPERTY(EditAnywhere,Category="")
    uint32 Maximum;

    // constructors
    FGameStats();
    FGameStats(const uint32 SetMax, const uint32 SetRemaining);
};
