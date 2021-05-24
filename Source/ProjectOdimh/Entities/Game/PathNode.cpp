// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "PathNode.h"
#include "Entities/Game/Obstacle.h"

// Sets default values
APathNode::APathNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    ClearObstacle();
}

const AObstacle* APathNode::GetObstacle() const
{
    return Obstacle;
}

void APathNode::SetObstacle(AObstacle* Set)
{
    Obstacle = Set;
}

void APathNode::ClearObstacle()
{
    Obstacle = NULL;
}

// Called when the game starts or when spawned
void APathNode::BeginPlay()
{
    Super::BeginPlay();
    
	
}

// Called every frame
void APathNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    

}

