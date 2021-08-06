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

void ATimestepGameplayOptions::NotifySave(USaveGame* Data)
{
    if(UPOdimhSaveGame* POdimhData = Cast<UPOdimhSaveGame>(Data))
    {
        for(auto& Map : TickingActors)
        {
            const FString& OrigValStr = *Map.Key->GetName() + FString(TEXT("Original"));
            const FString& CurrValStr = *Map.Key->GetName() + FString(TEXT("Current"));
            
            POdimhData->CustomInt.Add(OrigValStr, Map.Value.Original);
            POdimhData->CustomInt.Add(CurrValStr, Map.Value.Current);
            
            
        }
    }
}

const bool ATimestepGameplayOptions::NotifyLoad(USaveGame* Data)
{
    if(UPOdimhSaveGame* POdimhData = Cast<UPOdimhSaveGame>(Data))
    {
        for(auto& Map: TickingActors)
        {
            const FString& OrigValStr = *Map.Key->GetName() + FString(TEXT("Original"));
            const FString& CurrValStr = *Map.Key->GetName() + FString(TEXT("Current"));
            
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

const int ATimestepGameplayOptions::GetOnTickFrom(AActor* GameplayOption)
{
    int OnTick = -1;
    if(TickingActors.Contains(GameplayOption))
        OnTick = TickingActors[GameplayOption].Current;
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

void ATimestepGameplayOptions::TickStepTimer(AActor* CheckActor, const int OnTick)
{
    for(AActor* It : ShouldTick(OnTick))
    {
        if(IGameplayOptionsInterface* TimerTriggeredActor= Cast<IGameplayOptionsInterface>(It))
            TimerTriggeredActor->Run(true);
    }
}

const TArray<AActor*> ATimestepGameplayOptions::ShouldTick(const int OnTick)
{
    TArray<AActor*> CheckTickedActors;
    for(auto& Map : TickingActors)
    {
        if(OnTick % Map.Value.Current == 0)
            CheckTickedActors.Add(Map.Key);
    }
    
    return CheckTickedActors;
}
