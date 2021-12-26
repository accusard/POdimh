// Copyright 2017-2021 Vanny Sou. All Rights Reserved.


#include "Data/Tier.h"



void ATier::LevelUp(const uint32 PointValue, const uint32 Threshold)
{
    Level++;
    Points.Value = PointValue;
    SetThreshold(Threshold);
}

const int32 ATier::GetLevel() const
{
    return Level;
}

const int32 ATier::GetPointsForNextLevel() const
{
    return GetDeltaPoints();
}

void ATier::SetLevel(const uint32 NewLevel)
{
    if(NewLevel < 1)
    {
        Level = 1;
        return;
    }
    
    Level = NewLevel;
}

void ATier::SetLevel(const uint32 NewLevel, const uint32 PointValue, const uint32 Threshold)
{
    SetLevel(NewLevel);
    Points.Value = PointValue;
    SetThreshold(Threshold);
}
