// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Entities/States/State.h"
#include "Utilities/FGameStats.h"
#include "MomentumPlayState.generated.h"


/**
 * DEPRECATED
 */
UCLASS()
class PROJECTODIMH_API AMomentumPlayState : public AState
{
	GENERATED_BODY()
	
public:
    AMomentumPlayState();
    
    const uint32 GetCurrentTileComboCount() const;
    
    void SetMaximumTileComboCount(const uint32 NewCount);
    
    void IncrementTileComboCount();
    
private:
    /** The counter starts on the first match made and sequentially each tile matches after  each tile falls */
    FGameStats TileMatchComboCount;
	
	
};
