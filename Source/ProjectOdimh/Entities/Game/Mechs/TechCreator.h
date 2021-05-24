// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "TechCreator.generated.h"

class UTileMatchListener;
class UBaseEvent;

/**
 * 
 */
UCLASS()
class PROJECTODIMH_API ATechCreator : public AInfo
{
	GENERATED_BODY()
	
    
    
private:
    UTileMatchListener* TileMatch;
	
	
};
