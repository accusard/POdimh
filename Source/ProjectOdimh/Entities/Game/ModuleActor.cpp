// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "ModuleActor.h"
#include "Components/AimingComponent.h"

// Sets default values
AModuleActor::AModuleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AModuleActor::BeginPlay()
{
    Super::BeginPlay();
    
    if(!Tags.IsValidIndex(0))
    {
        UE_LOG(LogTemp, Warning, TEXT("Warning: an object of AModuleActor.."));
        
        if(!GetName().IsEmpty())
        {
            UE_LOG(LogTemp, Warning, TEXT("...ensure %s have a tag assigned in blueprint."), *GetName());
        }
    }
}

UActorComponent* AModuleActor::FindComponent(const UActorComponent* Comp) const
{
    UActorComponent* FoundedComp = nullptr;
    
    TInlineComponentArray<UActorComponent*> ModuleComponents;
    GetComponents(ModuleComponents);
    
    for(auto T : ModuleComponents)
    {
        if(T == Comp)
        {
            FoundedComp = T;
        }
    }
    return FoundedComp;
}

void AModuleActor::CopyTargetModule(AModuleActor* TargetModule, const bool bClearMyComponents)
{
    // clear this object's components
    if(bClearMyComponents)
    {
        TInlineComponentArray<UActorComponent*> MyModComp;
        GetComponents(MyModComp);
        ClearAllComponents(MyModComp);
    }
    
    // start copy of other object's components
    TInlineComponentArray<UActorComponent*> TargetModComp;
    TargetModule->GetComponents(TargetModComp);
    
    for(auto* T : TargetModComp)
    {
        CreateComponentFromTemplate(T);
    }
}

const bool AModuleActor::HasComponent(UActorComponent* Comp) const
{
    if(FindComponent(Comp))
        return true;
    
    return false;
}

void AModuleActor::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
    TagContainer = ModuleID;
}

void AModuleActor::ClearAllComponents(TInlineComponentArray<UActorComponent*> &ComponentList)
{
    for(auto* T : ComponentList)
    {
        T->DestroyComponent();
    }
}

