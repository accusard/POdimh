// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "ProjectOdimh.h"
#include "Components/StaticMeshComponent.h"
#include "TurretComponent.generated.h"


/**
 * The visual representation of the weapon's turret and its rotation behavior
 */
UCLASS(ClassGroup=(Weapons), meta=(BlueprintSpawnableComponent))
class PROJECTODIMH_API UTurretComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
    
    void RotateTurret(float Dir);
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGameplayTagContainer ModuleID;
    
private:
    // TODO: remove magic number
    /** The degree in which the turret can turn per second. */
    UPROPERTY(EditAnywhere, Category = "Setup")
    float MaxTurnPerSecond = 20.0f;
	
};
