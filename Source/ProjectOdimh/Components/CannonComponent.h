// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "ProjectOdimh.h"
#include "Components/StaticMeshComponent.h"
#include "CannonComponent.generated.h"


// TODO: remove magic numbers
/**
 * The visual representation of the weapon barrel and its behavior.
 */
UCLASS(ClassGroup=(Weapons), meta=(BlueprintSpawnableComponent))
class PROJECTODIMH_API UCannonComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
    void Elevate(float RelativeSpd);
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGameplayTagContainer ModuleID;
    
private:
    UPROPERTY(EditAnywhere, Category = "Setup")
    float   MaxDegreesPerSecond = 5.0f;
    
    UPROPERTY(EditAnywhere, Category = "Setup")
    float   MaxElevationDegrees = 40.0f;
    
    UPROPERTY(EditAnywhere, Category = "Setup")
    float   MinElevationDegrees = 0.0f;
	
	
};
