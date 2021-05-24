// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "ObstacleSpawner.h"
#include "Entities/Game/Obstacle.h"
#include "Engine/World.h"


AObstacle* UObstacleSpawner::Create(UWorld* World)
{
    AObstacle* Obstacle = nullptr;
    
    if(World)
    {
        if( (Obstacle = Cast<AObstacle>(World->SpawnActor(AObstacle::StaticClass()))) )
        {
            Obstacle->SetupInitialProperties();
            return Obstacle;
        }
    }
    
    return Obstacle;
}
