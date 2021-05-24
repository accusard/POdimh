// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "FinalScore.h"
#include "Entities/Factions/Faction.h"




UFinalScore::UFinalScore()
{
    OdimhFaction = nullptr;
    OrganicFaction = nullptr;
}

void UFinalScore::SetOdimhFaction(UFaction* Faction)
{
    OdimhFaction = Faction;
}
void UFinalScore::SetOrganicFaction(UFaction* Faction)
{
    OrganicFaction = Faction;
}

UFaction* UFinalScore::GetOdimhFaction() const
{
    return OdimhFaction;
}

UFaction* UFinalScore::GetOrganicFaction() const
{
    return OrganicFaction;
}
