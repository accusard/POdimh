// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "FGameStats.h"
#include "Data/Gametypes.h"

FGameStats::FGameStats()
{
    Current = DEFAULT_ONE;
    Original = DEFAULT_ONE;
}

FGameStats::FGameStats(const uint32 Max)
{
    FGameStats(Max, Max);
}

FGameStats::FGameStats(const uint32 Max, const uint32 Remaining)
{
    Original = Max;
    Current = Remaining;
}

