// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "FGameStats.h"
#include "Data/Gametypes.h"

FGameStats::FGameStats()
{
    Value = DEFAULT_ONE;
    Default = DEFAULT_ONE;
}

FGameStats::FGameStats(const uint32 Max) : FGameStats(Max, Max) {}

FGameStats::FGameStats(const uint32 Remaining, const uint32 Max)
{
    Default = Max;
    Value = Remaining;
}

