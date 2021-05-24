// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "ScoreTrackerComponent.h"


// Sets default values for this component's properties
UScoreTrackerComponent::UScoreTrackerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

    TotalScore = 0;
}

void UScoreTrackerComponent::Add(const int Value)
{
    if(Value <= 0)
        return;
    
    TotalScore += Value;
}

// Called when the game starts
void UScoreTrackerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

