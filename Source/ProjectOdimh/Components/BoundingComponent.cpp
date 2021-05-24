// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "BoundingComponent.h"
#if !UE_BUILD_SHIPPING
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"
#endif


// Sets default values for this component's properties
UBoundingComponent::UBoundingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Bounds = FBox(EForceInit::ForceInitToZero);
}

void UBoundingComponent::SetBounds(const FVector& Center, const FVector& Extent)
{
    // TODO: implement
    const FVector Min = Center - Extent;
    const FVector Max = Center + Extent;
    Bounds = FBox(Min, Max);
    
#if !UE_BUILD_SHIPPING
    FVector DebugCenter;
    FVector DebugExtent;
    Bounds.GetCenterAndExtents(DebugCenter, DebugExtent);
    UKismetSystemLibrary::DrawDebugBox(GetWorld(), DebugCenter, DebugExtent, FColor::Blue, FRotator::ZeroRotator, 2.f, 5.f);
#endif
}

// Called when the game starts
void UBoundingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBoundingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

