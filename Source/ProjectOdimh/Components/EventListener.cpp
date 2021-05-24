// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "EventListener.h"
#include "Events/GridEvent.h"

// Sets default values for this component's properties
UEventListener::UEventListener()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEventListener::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UEventListener::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


