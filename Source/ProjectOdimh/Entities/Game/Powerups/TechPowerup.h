// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Entities/Game/Powerups/Powerup.h"
#include "TechPowerup.generated.h"


/**
 * A powerup that give a mech capabilities in the form of an actor component
 */
UCLASS()
class PROJECTODIMH_API ATechPowerup : public APowerup
{
	GENERATED_BODY()
	
public:
    virtual void Activate(AActor* Target) override;
    
private:
    UPROPERTY(EditAnywhere)
    UActorComponent* TechComponent;
	
	
};
