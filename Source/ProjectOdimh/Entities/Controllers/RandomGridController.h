// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameTypes.h"
#include "Entities/Controllers/GridController.h"
#include "RandomGridController.generated.h"

/**
 * Deprecated - use a  blueprint class derived from AGridController instead
 */
UCLASS()
class PROJECTODIMH_API ARandomGridController : public AGridController
{
	GENERATED_BODY()
	
public:
    
    
    EDirection GetRandomDirection();
};
