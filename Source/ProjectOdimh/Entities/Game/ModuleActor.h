// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "ProjectOdimh.h"
#include "GameFramework/Actor.h"
#include "ModuleActor.generated.h"


/**
 * A containter for actor components associated with an ID type and tag name. Assign tags in blueprints. Actor
 * components that are created or copied through this object will be grouped by this object's tag name.
 */
UCLASS()
class PROJECTODIMH_API AModuleActor : public AActor, public IGameplayTagAssetInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AModuleActor();

    void BeginPlay() override;
    
    /** Check the component list and find the specified component */
    UActorComponent* FindComponent(const UActorComponent* Comp) const;
    
    /** Copy all component sets from another ModuleActor */
    void CopyTargetModule(AModuleActor* TargetModule, const bool bClearOldComponents = false);
    
    /** Checks the ModuleActor if it has the specified component */
    const bool HasComponent(UActorComponent* Comp) const;

    virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const;
    
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGameplayTagContainer ModuleID;
    
private:
    /** Set all components passed through this parameter to be destroyed */
    void ClearAllComponents(TInlineComponentArray<UActorComponent*> &ComponentList);
    
private:
	
};
