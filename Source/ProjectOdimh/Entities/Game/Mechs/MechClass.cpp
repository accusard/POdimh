// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "MechClass.h"
#include "Entities/Game/ModuleActor.h"



AMechClass::AMechClass()
{
    Hitpoints = INIT_HIT_POINTS;
}

const int32 AMechClass::GetHitPoints() const
{
    return Hitpoints;
}

TArray<AModuleActor*> AMechClass::GetTechModules()
{
    return TechModules;
}
