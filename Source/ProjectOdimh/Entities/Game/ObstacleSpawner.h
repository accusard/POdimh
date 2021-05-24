// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ObstacleSpawner.generated.h"

class AObstacle;

/**
 * 
 */
UCLASS()
class PROJECTODIMH_API UObstacleSpawner : public UObject
{
	GENERATED_BODY()
	
public:
    // TODO: create random obstacle
    AObstacle* Create(UWorld* World);
	
	
};
