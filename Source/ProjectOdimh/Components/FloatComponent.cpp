// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "FloatComponent.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UFloatComponent::UFloatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

    XMultiplier = 5.f;
    ZMultiplier = 5.f;
}


// Called when the game starts
void UFloatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFloatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    FVector NewLocation = GetOwner()->GetActorLocation();
    float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));

    NewLocation.X += DeltaHeight * XMultiplier;
    NewLocation.Y += DeltaHeight * YMultiplier;
    NewLocation.Z += DeltaHeight * ZMultiplier;

    RunningTime += DeltaTime;
    GetOwner()->SetActorLocation(NewLocation);
}

