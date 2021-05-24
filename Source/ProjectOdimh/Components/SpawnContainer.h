// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpawnContainer.generated.h"




/**
 * A SpawnContainer object spawns an actor when the owner of the component is destroyed
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTODIMH_API USpawnContainer : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpawnContainer();

    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    
    /** Sets the actor that will spawn when the owner of this component is destroyed */
    void SetContainer(TSubclassOf<AActor> SpawningActor, const FTransform &Transform);
    
    /** Handle the event when an actor is destroyed */
    UFUNCTION()
    void OnOwnerDestroyed(AActor* DestroyedActor);

    AActor* Spawn(TSubclassOf<AActor> Actor, const FTransform &Transform);
    
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category="Spawning Properties")
    uint16 bUseOwnerTransformWhenSpawning : 1;
    
    UPROPERTY(EditAnywhere, Category="Spawning Properties")
    uint16 bSpawnFromContainerWhenOwnerDestroyed : 1;

    /** Spawn this when the component is destroyed. Can be assigned in Blueprint */
    UPROPERTY(EditAnywhere, Category="Spawning Properties")
    TSubclassOf<AActor> Container;

    FTransform SpawnTransform;
};
