// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "CannonComponent.h"


void UCannonComponent::Elevate(float RelativeSpd)
{
    // move barrel the right amount
    RelativeSpd = FMath::Clamp<float>(RelativeSpd, -1.f, +1.f);
    float ElevationChange = RelativeSpd * MaxDegreesPerSecond * GetWorld()->GetDeltaSeconds();
    float RawElevation = RelativeRotation.Pitch + ElevationChange;
    auto Elevation = FMath::ClampAngle(RawElevation, MinElevationDegrees, MaxElevationDegrees);
    
    // rotate pitch only
    SetRelativeRotation(FRotator(Elevation, 0.f, 0.f));
    
}

