// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "ActorPickHandlerComponent.h"
#include "POdimhGameInstance.h"
#include "ClassInterface/PickHandlerInterface.h"


// Sets default values for this component's properties
UActorPickHandlerComponent::UActorPickHandlerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

    bPickedIsControlledByPlayer = false;
    
    
}

void UActorPickHandlerComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    
        
}

const bool UActorPickHandlerComponent::IsActorPickedPlayerControlled() const
{
    if(!ActorPicked)
        return false;
    
    return bPickedIsControlledByPlayer;
}

void UActorPickHandlerComponent::NotifyActorPicked()
{
    Cast<UPOdimhGameInstance>(GetOwner()->GetGameInstance())->EventManager->OnActorPicked.Broadcast(ActorPicked);
}

void UActorPickHandlerComponent::NotifyReleasePickedActor()
{
    Cast<UPOdimhGameInstance>(GetOwner()->GetGameInstance())->EventManager->OnActorReleased.Broadcast(ActorPicked);
    SetPlayerControlled(false);
    ActorPicked = nullptr;
}

void UActorPickHandlerComponent::SetPlayerControlled(const bool bIsControlledByPlayer /* = true */)
{
    bPickedIsControlledByPlayer = bIsControlledByPlayer;
}
