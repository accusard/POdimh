// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "ProjectOdimh.h"
#include "Components/StaticMeshComponent.h"
#include "ArmorComponent.generated.h"


/**
 * 
 */
UCLASS(ClassGroup=(Defenses), meta=(BlueprintSpawnableComponent))
class PROJECTODIMH_API UArmorComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGameplayTagContainer ModuleID;
	
	
};
