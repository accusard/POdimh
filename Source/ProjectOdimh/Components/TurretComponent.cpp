// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "TurretComponent.h"


void UTurretComponent::RotateTurret(float Dir)
{
    Dir = FMath::Clamp<float>(Dir, -1.f, +1.f);
    auto DeltaRotation = Dir * MaxTurnPerSecond * GetWorld()->GetDeltaSeconds();
    auto RawRotation = RelativeRotation.Yaw + DeltaRotation;
    
    // rotate along the yaw only
    SetRelativeRotation(FRotator(0.f, RawRotation, 0.f));
}

