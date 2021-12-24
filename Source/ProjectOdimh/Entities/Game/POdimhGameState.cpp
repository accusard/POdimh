// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "POdimhGameState.h"
#include "Data/Tier.h"

APOdimhGameState::APOdimhGameState() : bGameHasStarted(false)
{
    Score = GetWorld()->SpawnActor<APointTracker>();
    ScoreTier = GetWorld()->SpawnActor<ATier>();
}

void APOdimhGameState::AddToScore(const int32 Points, const int32 Multiplier)
{
    ScoreMultiplier = Multiplier;
    GetScore()->Add(Points, ScoreMultiplier);
}

const uint32 APOdimhGameState::GetTotalScore() const
{
    return Score->GetTotalPoints();
}

void APOdimhGameState::AddToTierPoints(const uint32 Points)
{
    GetScoreTier()->Add(Points);
}

const uint32 APOdimhGameState::GetTierLevel() const
{
    return ScoreTier->GetLevel();
}
