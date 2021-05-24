// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "FGameStats.h"
#include "Gametypes.h"

FGameStats::FGameStats()
{
    Remaining = DEFAULT_MOVE_COST;
    Maximum = DEFAULT_MOVE_COST;
}

FGameStats::FGameStats(const uint32 SetMax, const uint32 SetRemaining)
{
    // TODO: need to increase maximum value
    Maximum = FMath::Clamp<uint32>(SetMax, DEFAULT_MOVE_COST, MAXIMUM_VALUE_1000);
    Remaining = FMath::Clamp<uint32>(SetRemaining, 0, Maximum);
}

