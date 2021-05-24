// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "EventTriggerCapsule.h"
#include "Entities/Game/Match3GameMode.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Events/BaseEvent.h"

AEventTriggerCapsule::AEventTriggerCapsule()
{
    OnActorBeginOverlap.AddDynamic(this, &AEventTriggerCapsule::OnEnter);
}

void AEventTriggerCapsule::OnEnter(AActor* ThisActor, AActor* OtherActor)
{
    // let the the other actor knows that it entered this capsule
    AMatch3GameMode* Mode = Cast<AMatch3GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
    

}


