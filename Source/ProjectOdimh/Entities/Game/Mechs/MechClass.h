// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "Utilities/FGameStats.h"
#include "MechClass.generated.h"

class AModuleActor;

/**
 * Defines the properties of a Mech
 */
UCLASS()
class PROJECTODIMH_API AMechClass : public AInfo
{
	GENERATED_BODY()
	
    AMechClass();
    
    UPROPERTY(EditAnywhere)
    FString Name;
    
    const int32 GetHitPoints() const;
    
    TArray<AModuleActor*> GetTechModules();
    
private:
    UPROPERTY(EditAnywhere)
    int32 Hitpoints;
    
    /** The combined modules that make up the class of this mech */
    UPROPERTY(EditAnywhere)
	TArray<AModuleActor*> TechModules;
};
