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
    
    void NotifyActorPicked();
    void NotifyReleasePickedActor();
    
    void SetPlayerControlled(const bool bIsControlledByPlayer = true);
    const bool IsActorPickedPlayerControlled() const;
    
    
protected:
    

private:
    AActor* ActorLastPicked;
    AActor* ActorPicked;
    bool bPickedIsControlledByPlayer;
};
