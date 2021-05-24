// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "Faction.h"
#include "Entities/Factions/Pledge.h"


const int32 UFaction::GetTotalNumberOfPledges() const
{
    return TotalPledges.Num();
}

void UFaction::AddPledge(UPledge* Pledge)
{
    TotalPledges.Add(Pledge);
}
