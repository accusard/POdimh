// Copyright 2017-2019 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorPickHandlerComponent.generated.h"

class ATile;
class USoundCue;
class AGrid;



/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTODIMH_API UActorPickHandlerComponent : public UActorComponent
{
	GENERATED_BODY()

    friend class IPickHandlerInterface;
    friend class AGrid;
    
public:	
	// Sets default values for this component's properties
	UActorPickHandlerComponent();
    
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    
    void NotifyActorPicked(const bool bMakeNewHandledList = true);
    void NotifyReleasePickedActor();
    
    const bool ActorsHandledByPlayer() const;
    
    void AddHandledActor(AActor* Actor);
    TArray<AActor*> &GetAllActorsHandledByThisComp();
    void ClearActorsHandledByThisComp();
    
protected:
    

private:
    AActor* ActorLastPicked;
    AActor* ActorPicked;
    bool bPickedIsControlledByPlayer;
    
    UPROPERTY()
    TArray<AActor*> HandledActors;
};
