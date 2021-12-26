// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "POdimhGameState.h"
#include "Data/Tier.h"

APOdimhGameState::APOdimhGameState() : bGameHasStarted(false)
{
    Score = CreateDefaultSubobject<APointTracker>("Score");
    TierProgression = CreateDefaultSubobject<ATier>("TierProgression");
    
    Score->SetThreshold(DEFAULT_HIGH_SCORE);
    TierProgression->SetThreshold(DEFAULT_NEXT_TIER_LEVEL);
    
}
