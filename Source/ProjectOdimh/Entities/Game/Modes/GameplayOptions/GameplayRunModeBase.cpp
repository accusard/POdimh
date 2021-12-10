// Copyright 2017-2021 Vanny Sou. All Rights Reserved.


#include "TimestepGameplayOptions.h"
#include "POdimhGameInstance.h"
#include "ClassInterface/GameplayOptionsInterface.h"


// Sets default values
AGameplayRunModeBase::AGameplayRunModeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AGameplayRunModeBase::Save(USaveGame* Data)
{
    if(UPOdimhSaveGame* POdimhData = Cast<UPOdimhSaveGame>(Data))
    {
        for(auto& Map : TickingActors)
        {
            const FString& OrigValStr = *Map.Key->GetName() + FString("Original");
            const FString& CurrValStr = *Map.Key->GetName() + FString("Current");
            
            POdimhData->CustomInt.Add(OrigValStr, Map.Value.Original);
            POdimhData->CustomInt.Add(CurrValStr, Map.Value.Current);
        }
    }
}

const bool AGameplayRunModeBase::Load(USaveGame* Data)
{
    if(UPOdimhSaveGame* POdimhData = Cast<UPOdimhSaveGame>(Data))
    {
        for(auto& Map: TickingActors)
        {
            const FString& OrigValStr = *Map.Key->GetName() + FString("Original");
            const FString& CurrValStr = *Map.Key->GetName() + FString("Current");
            
            Map.Value.Original = *POdimhData->CustomInt.Find(OrigValStr);
            Map.Value.Current = *POdimhData->CustomInt.Find(CurrValStr);
        }
        
        return true;
    }
    
    return false;
}

// Called when the game starts or when spawned
void AGameplayRunModeBase::BeginPlay()
{
	Super::BeginPlay();
    
    UEventManager* EvtMgr = Cast<UPOdimhGameInstance>(GetGameInstance())->EventManager;
    EvtMgr->CallBackOnStepTick.AddDynamic(this, &AGameplayRunModeBase::TickStepTimer);
}

const int AGameplayRunModeBase::GetOnTickFrom(AActor* Gameplay)
{
    int OnTick = -1;
    if(TickingActors.Contains(Gameplay))
        OnTick = TickingActors[Gameplay].Current;
    return OnTick;
}

void AGameplayRunModeBase::AddActorToTick(AActor* Actor, const FGameStats& TickOnCount)
{
    TickingActors.Add(Actor, TickOnCount);
}

void AGameplayRunModeBase::ResetActorsTickCounter(TArray<AActor*> AllActors)
{
    for(AActor* It : AllActors)
    {
        if(TickingActors.Contains(It))
            TickingActors[It].Current = TickingActors[It].Original;
    }
}

void AGameplayRunModeBase::SetActorToTickOn(AActor* SetActor, const int TickOn)
{
    if(TickingActors.Contains(SetActor))
        TickingActors[SetActor].Current = TickOn;
}

void AGameplayRunModeBase::ResetAllActorsTickCounter()
{
    for(auto& Map : TickingActors)
        Map.Value = FGameStats(TickCounter);
}

void AGameplayRunModeBase::TickStepTimer(AActor* ActPtr, const int OnTick)
{
    if(TickingActors.Num() > 0)
    {
        if(ShouldTick(ActPtr, OnTick))
        {
            if(IGameplayOptionsInterface* TickActor = Cast<IGameplayOptionsInterface>(ActPtr))
                TickActor->Execute_Run(ActPtr);
        }
    }
}

const int AGameplayRunModeBase::GetTickOnTurn(AActor* CheckActor, const int CurrTurn)
{
    const int TickOn = GetOnTickFrom(CheckActor);
    
    if(TickOn > 0)
    {
        int TurnsBeforeTick = CurrTurn;
        while(TurnsBeforeTick % TickOn != 0)
            TurnsBeforeTick++;
        
        return (TurnsBeforeTick - CurrTurn) + 1;
    }
    return TickOn;
}

const bool AGameplayRunModeBase::ShouldTick(AActor* CheckActor, const int OnTick)
{
    if(TickingActors.Contains(CheckActor))
        return TickingActors[CheckActor].Current == 0 || OnTick % TickingActors[CheckActor].Current == 0;
    
    return false;
}

const TArray<AActor*> AGameplayRunModeBase::ShouldTick(const int OnTick)
{
    TArray<AActor*> CheckTickedActors;
    for(auto& Map : TickingActors)
    {
        if(Map.Value.Current == 0 || OnTick % Map.Value.Current == 0)
            CheckTickedActors.Add(Map.Key);
    }
    
    return CheckTickedActors;
}
