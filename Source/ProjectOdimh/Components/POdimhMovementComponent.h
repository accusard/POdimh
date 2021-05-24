// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "ProjectOdimh.h"
#include "GameFramework/PawnMovementComponent.h"
#include "POdimhMovementComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Navigations), meta=(BlueprintSpawnableComponent))
class PROJECTODIMH_API UPOdimhMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()
	
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGameplayTagContainer ModuleID;
	
	
};
