// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "ProjectOdimh.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


/**
 * A component that tracks and calculates the health percentage of an entity.
 * Intended to be use with a Widget Component that is added in the entity's Blueprint.
 */
UCLASS( ClassGroup=(Defenses), meta=(BlueprintSpawnableComponent) )
class PROJECTODIMH_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGameplayTagContainer ModuleID;
    
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
