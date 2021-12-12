// Copyright 2017-2021 Vanny Sou. All Rights Reserved.


#include "Entities/Game/Modes/GameplayOptions/Gameplay.h"
#include "Events/EventManager.h"

// Sets default values
AGameplay::AGameplay()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AGameplay::SetNumTicksBeforeRun(const uint32 Set)
{
    NumOfTicksBeforeRun = Set;
}

void AGameplay::Init_Implementation(AActor* Actor, UBaseEvent* EvtPtr)
{
    // unbind the Init event
    // blueprint must call to parent after it finishes initialization
    EvtPtr->Manager->OnActorEvent.RemoveDynamic(this, &AGameplay::Init);
}
