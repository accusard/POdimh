// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "BaseMech.h"
#include "Engine/World.h"
#include "Entities/Game/ModuleActor.h"
#include "Kismet/GameplayStatics.h"

void ABaseMech::BeginPlay()
{
//    WeaponModule = AttachModuleToSocket(WeaponBlueprint, TEXT("Mount_Top"));
}

AModuleActor* ABaseMech::AttachModuleToSocket(TSubclassOf<AModuleActor> ModuleBlueprint, FName SocketName)
{
    AModuleActor* Module = nullptr;
    
    if(ModuleBlueprint)
    {
        // spawn and attach to socket
        Module = GetWorld()->SpawnActor<AModuleActor>(WeaponBlueprint);
        Module->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), SocketName);
    }
    
    return Module;
}
