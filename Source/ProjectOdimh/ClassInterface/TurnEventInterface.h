// Copyright 2022 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TurnEventInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTurnEventInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTODIMH_API ITurnEventInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void OnTurnEnd(AActor* EvtCaller, class UGameEvent* Event);
};
