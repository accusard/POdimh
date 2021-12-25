// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "POdimhGameState.h"
#include "Data/Tier.h"

APOdimhGameState::APOdimhGameState() : bGameHasStarted(false)
{
    Score = GetWorld()->SpawnActor<APointTracker>();
    Score->SetThreshold(DEFAULT_HIGH_SCORE);
    TierProgression->SetThreshold(DEFAULT_NEXT_TIER_LEVEL);
    TierProgression = GetWorld()->SpawnActor<ATier>();
}
