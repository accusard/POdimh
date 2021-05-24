// Copyright 2017-2019 Vanny Sou. All Rights Reserved.

#include "ActionTurnBasedComponent.h"
#include "GameTypes.h"
#include "Entities/Game/ParticipantTurn.h"


// Sets default values for this component's properties
UActionTurnBasedComponent::UActionTurnBasedComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
    ActionCount = FGameStats();
}

const bool UActionTurnBasedComponent::TryExecute(const FMatch3GameAction& Action)
{
    ActionCount = FGameStats(Action.Num, Action.Num);
    LastActionCommitted = Action;
    return true;
}

void UActionTurnBasedComponent::ResetActions()
{
    RestoreActionMax();
}

void UActionTurnBasedComponent::RestoreActionMax()
{
    ActionCount.Remaining = ActionCount.Maximum;
}

// Called when the game starts
void UActionTurnBasedComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

const int32 UActionTurnBasedComponent::GetRemainingActions() const
{
    return ActionCount.Remaining;
}

