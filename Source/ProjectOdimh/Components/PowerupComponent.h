// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PowerupComponent.generated.h"

class APowerup;

/**
 * Keeps a list of powerups
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTODIMH_API UPowerupComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPowerupComponent();

    /** Add a new powerup and activate it if desired */
    void Add(APowerup* Powerup, const bool bActivate = true);
    
    /** Attempt to activate powerup properties and return true if the powerup is in the active list */
    const bool Enable(APowerup* Powerup);
    
    /** Attempt to deactivate the powerup properties and remove it from the list if desired*/
    void Disable(APowerup* Powerup, const bool bRemove = false);
    
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
    TArray<APowerup*> ActivePowerups;
	
};
