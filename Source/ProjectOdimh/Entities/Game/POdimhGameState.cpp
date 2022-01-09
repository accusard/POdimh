// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "POdimhGameState.h"
#include "Data/Tier.h"
#include "Data/Gametypes.h"

APOdimhGameState::APOdimhGameState() : bGameHasStarted(false)
{
    Score = CreateDefaultSubobject<APoints>("Score");
    TierProgression = CreateDefaultSubobject<ATier>("TierProgression");
    
    Score->SetThreshold(DEFAULT_HIGH_SCORE);
    TierProgression->SetThreshold(ATier::DEFAULT_NEXT_TIER);
    
}
