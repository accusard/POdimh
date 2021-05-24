// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FloatComponent.generated.h"

/**
 * The component add functionality to an actor and causes it to update its position based on a multiplier value, thus giving the appearance
 * of the actor floating.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTODIMH_API UFloatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFloatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    float RunningTime;
    UPROPERTY(EditAnywhere)
    float XMultiplier;
    UPROPERTY(EditAnywhere)
    float YMultiplier;
    UPROPERTY(EditAnywhere)
    float ZMultiplier;
};
