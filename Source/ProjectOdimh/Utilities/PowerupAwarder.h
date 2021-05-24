// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class AActor;
class APowerup;

/**
 * Awards a powerup to an entity
 */
class PROJECTODIMH_API PowerupAwarder
{
public:
	PowerupAwarder();
    
    void BestowPowerup(AActor* Target, APowerup* Powerup);
    
	~PowerupAwarder();
};
