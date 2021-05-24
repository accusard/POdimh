// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerCapsule.h"
#include "EventTriggerCapsule.generated.h"

/**
 * A trigger capsule with a GameEventType
 */
UCLASS()
class PROJECTODIMH_API AEventTriggerCapsule : public ATriggerCapsule
{
	GENERATED_BODY()
	
public:
    // constructor
    AEventTriggerCapsule();
    
    /** When an actor enters this trigger box */
    UFUNCTION()
    void OnEnter(AActor* ThisActor, AActor* OtherActor);
	
public:
};
