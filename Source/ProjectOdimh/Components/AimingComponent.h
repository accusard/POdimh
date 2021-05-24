// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "ProjectOdimh.h"
#include "Components/ActorComponent.h"
#include "AimingComponent.generated.h"


/** Enum to track the firing state of an aiming component */
UENUM()
enum class EFiringState : uint8
{
    AIMING,
    RELOADING,
    LOCKED,
    NOAMMO
};

/**
 * An AimingComponent object handles the transformation of a StaticMeshComponent objects.
 */
UCLASS( ClassGroup=(Weapons), meta=(BlueprintSpawnableComponent) )
class PROJECTODIMH_API UAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAimingComponent();

    /** Returns the firing state of the aiming component */
    const EFiringState& GetFiringState() const;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGameplayTagContainer ModuleID;
    
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:
    /** An enum to track the firing state of the aiming component. In Blueprint, changes the color of the crosshair based on its firing state. */
    UPROPERTY(BlueprintReadOnly)
    EFiringState FiringState;
    
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
