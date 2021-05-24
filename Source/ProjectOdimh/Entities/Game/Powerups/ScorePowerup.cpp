// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "ScorePowerup.h"
#include "Components/ScoreTrackerComponent.h"

void AScorePowerup::SetScoreValue(const int SetValue)
{
    ScoreValue = SetValue;
}

void AScorePowerup::Activate(AActor* Target)
{
    UScoreTrackerComponent* Score = Target->FindComponentByClass<UScoreTrackerComponent>();
    if(Score)
    {
        Score->Add(ScoreValue);
    }
}
