// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "PowerupComponent.h"
#include "Entities/Game/Powerups/Powerup.h"


// Sets default values for this component's properties
UPowerupComponent::UPowerupComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UPowerupComponent::Add(APowerup* Powerup, const bool bActivate /*= true*/)
{
    ActivePowerups.Add(Powerup);
    
    if(bActivate)
        Powerup->Activate(GetOwner());
}

const bool UPowerupComponent::Enable(APowerup* Powerup)
{
    const bool bHasPowerup = ActivePowerups.Contains(Powerup);
    if(bHasPowerup)
    {
        Powerup->Activate(GetOwner());
        return true;
    }
    
    return false;
}

void UPowerupComponent::Disable(APowerup* Powerup, const bool bRemove /* = false*/)
{
    const bool bHasPowerup = ActivePowerups.Contains(Powerup);
    
    if(bHasPowerup)
    {
        Powerup->Deactivate(GetOwner());
        if(bRemove)
        {
            ActivePowerups.Remove(Powerup);
        }
    }
}
// Called when the game starts
void UPowerupComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

