// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "State.generated.h"

/**
 * DEPRECATED
 * Abstract class for a state entity
 */
UCLASS()
class PROJECTODIMH_API AState : public AGameStateBase
{
    GENERATED_BODY()

    
public:
	AState();
    
    virtual void Start();
    
    virtual void End();

    UPROPERTY(BlueprintReadWrite)
    int32 ID;
};
