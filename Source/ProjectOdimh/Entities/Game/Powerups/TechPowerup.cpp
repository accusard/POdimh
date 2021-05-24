// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "TechPowerup.h"
#include "Entities/Game/ModuleActor.h"



void ATechPowerup::Activate(AActor* Target)
{
    if(TechComponent)
    {
        Target->CreateComponentFromTemplate(TechComponent);
    }
}
