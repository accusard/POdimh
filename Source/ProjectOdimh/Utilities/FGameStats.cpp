// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "FGameStats.h"
#include "Data/Gametypes.h"

FGameStats::FGameStats()
{
    Current = DEFAULT_MOVE_COST;
    Original = DEFAULT_MOVE_COST;
}

FGameStats::FGameStats(const uint32 SetMax, const uint32 SetRemaining)
{
    // TODO: need to increase maximum value
    Original = FMath::Clamp<uint32>(SetMax, DEFAULT_MOVE_COST, MAXIMUM_VALUE_1000);
    Current = FMath::Clamp<uint32>(SetRemaining, 0, Original);
}

