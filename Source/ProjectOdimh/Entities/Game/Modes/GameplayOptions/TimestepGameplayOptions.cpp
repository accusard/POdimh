// Copyright 2017-2021 Vanny Sou. All Rights Reserved.


#include "Entities/Game/Modes/GameplayOptions/TimestepGameplayOptions.h"
#include "POdimhGameInstance.h"
#include "ClassInterface/GameplayOptionsInterface.h"


// Sets default values
ATimestepGameplayOptions::ATimestepGameplayOptions()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ATimestepGameplayOptions::Save(USaveGame* Data)
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

const bool ATimestepGameplayOptions::Load(USaveGame* Data)
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
void ATimestepGameplayOptions::BeginPlay()
{
	Super::BeginPlay();
    
    UEventManager* EvtMgr = Cast<UPOdimhGameInstance>(GetGameInstance())->EventManager;
    EvtMgr->CallBackOnStepTick.AddDynamic(this, &ATimestepGameplayOptions::TickStepTimer);
}

const int ATimestepGameplayOptions::GetOnTickFrom(AActor* Gameplay)
{
    int OnTick = -1;
    if(TickingActors.Contains(Gameplay))
        OnTick = TickingActors[Gameplay].Current;
    return OnTick;
}

void ATimestepGameplayOptions::AddActorToTick(AActor* Actor, const FGameStats& TickOnCount)
{
    TickingActors.Add(Actor, TickOnCount);
}

void ATimestepGameplayOptions::ResetActorsTickCounter(TArray<AActor*> AllActors)
{
    for(AActor* It : AllActors)
    {
        if(TickingActors.Contains(It))
            TickingActors[It].Current = TickingActors[It].Original;
    }
}

void ATimestepGameplayOptions::SetActorToTickOn(AActor* SetActor, const int TickOn)
{
    if(TickingActors.Contains(SetActor))
        TickingActors[SetActor].Current = TickOn;
}

void ATimestepGameplayOptions::ResetAllActorsTickCounter()
{
    for(auto& Map : TickingActors)
        Map.Value = FGameStats(TickCounter);
}

void ATimestepGameplayOptions::TickStepTimer(AActor* ActPtr, const int OnTick)
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

const int ATimestepGameplayOptions::GetTickOnTurn(AActor* CheckActor, const int CurrTurn)
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

const bool ATimestepGameplayOptions::ShouldTick(AActor* CheckActor, const int OnTick)
{
    if(TickingActors.Contains(CheckActor))
        return TickingActors[CheckActor].Current == 0 || OnTick % TickingActors[CheckActor].Current == 0;
    
    return false;
}

const TArray<AActor*> ATimestepGameplayOptions::ShouldTick(const int OnTick)
{
    TArray<AActor*> CheckTickedActors;
    for(auto& Map : TickingActors)
    {
        if(Map.Value.Current == 0 || OnTick % Map.Value.Current == 0)
            CheckTickedActors.Add(Map.Key);
    }
    
    return CheckTickedActors;
}
