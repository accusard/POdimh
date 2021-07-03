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

const bool UActorPickHandlerComponent::ActorsHandledByPlayer() const
{
    if(HandledActors.Num() > 0 && Cast<APlayerController>(GetOwner()))
        return true;
    else
        return false;
}

void UActorPickHandlerComponent::NotifyActorPicked(const bool bMakeNewHandledList)
{
    if(bMakeNewHandledList)
        ClearActorsHandledByThisComp();
    
    Cast<UPOdimhGameInstance>(GetOwner()->GetGameInstance())->EventManager->OnActorPicked.Broadcast(ActorPicked);
}

void UActorPickHandlerComponent::NotifyReleasePickedActor()
{
    Cast<UPOdimhGameInstance>(GetOwner()->GetGameInstance())->EventManager->OnActorReleased.Broadcast(ActorPicked);
    ActorPicked = nullptr;
    
    for(auto i : GetAllActorsHandledByThisComp())
    {
        UE_LOG(LogTemp, Warning, TEXT("Handled: %s"), *i->GetName());
    }
}

void UActorPickHandlerComponent::AddHandledActor(AActor* Actor)
{
    HandledActors.AddUnique(Actor);
}

TArray<AActor*> &UActorPickHandlerComponent::GetAllActorsHandledByThisComp()
{
    return HandledActors;
}

void UActorPickHandlerComponent::ClearActorsHandledByThisComp()
{
    HandledActors.Empty();
}
