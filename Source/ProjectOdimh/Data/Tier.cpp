// Copyright 2017-2021 Vanny Sou. All Rights Reserved.


#include "Data/Tier.h"



void ATier::Levelup(const uint32 PointValue, const uint32 Threshold)
{
    Level++;
    Points.Value = PointValue;
    SetThreshold(Threshold);
}

const uint32 ATier::GetLevel() const
{
    return Level;
}

const uint32 ATier::GetNextLevelUp() const
{
    const uint32 Diff = GetThreshold() - Points.Value;
    return Diff;
}

void ATier::SetLevel(const uint32 Set, const uint32 PointValue, const uint32 Threshold)
{
    Level = Set;
    Points.Value = PointValue;
    SetThreshold(Threshold);
}
