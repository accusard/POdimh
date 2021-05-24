// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "PathNodeMovement.h"
#include "Entities/Game/PathNode.h"
#include "Entities/Game/Pathways.h"

// Sets default values for this component's properties
UPathNodeMovement::UPathNodeMovement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

const bool UPathNodeMovement::TryMoveTo(APathways* Path, APathNode* Node) const
{
    if(Node->GetObstacle() || !Path->Move(Node))
        return false;
    
    return true;
}

// Called when the game starts
void UPathNodeMovement::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

