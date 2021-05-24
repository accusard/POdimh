// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/SkeletalMeshActor.h"
#include "BaseMech.generated.h"

class AModuleActor;
/**
 * 
 */
UCLASS()
class PROJECTODIMH_API ABaseMech : public ASkeletalMeshActor
{
	GENERATED_BODY()
	
public:
    void BeginPlay();
    
    /** Attach a AModuleActor blueprint to a socket and return that module */
    AModuleActor* AttachModuleToSocket(TSubclassOf<AModuleActor> ModuleBlueprint, FName SocketName);
    
private:
    /** The blueprint class of the weapon */
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<AModuleActor> WeaponBlueprint;
    
    /** The reference to the WeaponModule of this ABaseMech object */
    AModuleActor* WeaponModule;
};
