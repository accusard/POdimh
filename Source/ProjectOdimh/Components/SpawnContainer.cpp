// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "SpawnContainer.h"
#include "ProjectOdimh.h"
#include "Engine/World.h"
#include "Events/GridEvent.h"



// Sets default values for this component's properties
USpawnContainer::USpawnContainer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
    bUseOwnerTransformWhenSpawning = true;
    bSpawnFromContainerWhenOwnerDestroyed = true;
}


// Called when the game starts
void USpawnContainer::BeginPlay()
{
	Super::BeginPlay();
    
    GetOwner()->OnDestroyed.AddUniqueDynamic(this, &USpawnContainer::OnOwnerDestroyed);
    
}


// Called every frame
void USpawnContainer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void USpawnContainer::SetContainer(TSubclassOf<AActor> SpawningActor, const FTransform &Transform)
{
    Container = SpawningActor;
    SpawnTransform = Transform;
}

void USpawnContainer::OnOwnerDestroyed(AActor* DestroyedActor)
{
    if(bSpawnFromContainerWhenOwnerDestroyed && DestroyedActor == GetOwner() && Container)
    {
        if(bUseOwnerTransformWhenSpawning)
            SpawnTransform = DestroyedActor->GetTransform();
        
        if(UPOdimhGameInstance* GameInstance = Cast<UPOdimhGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
        {
            if(DestroyedActor)
            {
                GameInstance->EventManager->NewEvent<UGridEvent>(GetWorld(), "Grid Event", true);
                GameInstance->EventManager->OnSpawnFromComponent.Broadcast(Spawn(Container, SpawnTransform), this);
            }
        }
    }
}


AActor* USpawnContainer::Spawn(TSubclassOf<AActor> Class, const FTransform &Transform)
{
    return GetOwner()->GetWorld()->SpawnActor(Class, &Transform);
}

