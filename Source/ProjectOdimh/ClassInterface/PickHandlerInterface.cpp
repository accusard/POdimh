// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "PickHandlerInterface.h"
#include "Components/ActorPickHandlerComponent.h"


// Add default functionality here for any IPickHandlerInterface functions that are not pure virtual.





AActor* IPickHandlerInterface::GetLastGrab(UActorPickHandlerComponent* Comp)
{
    return Comp->ActorLastPicked;
}

AActor* IPickHandlerInterface::GetActorPicked(UActorPickHandlerComponent* Comp)
{
    return Comp->ActorPicked;
}

AActor* IPickHandlerInterface::GrabActor(AActor* InterfaceHandler, UActorPickHandlerComponent* PickHandler, const FHitResult& Hit)
{
    return GrabActor(InterfaceHandler, PickHandler, Hit.GetActor(), Hit.ImpactPoint);
}

AActor* IPickHandlerInterface::GrabActor(AActor* InterfaceHandler, UActorPickHandlerComponent* PickHandler, AActor* TargetGrab, const FVector& GrabLocation)
{
    if(Cast<IPickHandlerInterface>(InterfaceHandler) && InterfaceHandler->FindComponentByClass(PickHandler->GetClass()))
    {
        if(TargetGrab)
        {
            PickHandler->ActorLastPicked = TargetGrab;
            PickHandler->ActorPicked = TargetGrab;
            PickHandler->NotifyActorPicked();
            Execute_OnPickActor(InterfaceHandler, GrabLocation);
        }
        return GetLastGrab(PickHandler);
    }
    return nullptr;
}

const bool IPickHandlerInterface::IsActorPicked(UActorPickHandlerComponent* Comp)
{
    return Comp->ActorPicked ? true : false;
}

void IPickHandlerInterface::OnReleaseActor_Implementation(UActorPickHandlerComponent* PickHandler)
{
    if(PickHandler && PickHandler->ActorPicked)
    {
        PickHandler->NotifyReleasePickedActor();
    }
}
