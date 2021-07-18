// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "POdimhGameState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTODIMH_API APOdimhGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
    UPROPERTY(BlueprintReadOnly)
    int32 RoundCounter;
    
    uint32 TurnCounter;
    uint32 ParticipantIndex;
    
    /** Tracks the current score of the game */
    UPROPERTY()
    int32 CurrentScore;

};
