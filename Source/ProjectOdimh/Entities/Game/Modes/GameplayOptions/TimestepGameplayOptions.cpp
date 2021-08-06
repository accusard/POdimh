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
            POdimhData->CustomInt.Add(*Map.Key->GetName(), Map.Value);
    }
}

const bool ATimestepGameplayOptions::NotifyLoad(USaveGame* Data)
{
    if(UPOdimhSaveGame* POdimhData = Cast<UPOdimhSaveGame>(Data))
    {
        for(auto& Map: TickingActors)
        {
            const FString& Name = *Map.Key->GetName();
            Map.Value = *POdimhData->CustomInt.Find(Name);
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
    EvtMgr->CallBackWithCount.AddDynamic(this, &ATimestepGameplayOptions::TickStepTimer);
}

const int ATimestepGameplayOptions::GetStepTimer(AActor* GameplayOption)
{
    int StepTimer = -1;
    if(TickingActors.Contains(GameplayOption))
        StepTimer = TickingActors[GameplayOption];
    return StepTimer;
}

void ATimestepGameplayOptions::AddActorToTick(AActor* Actor)
{
    TickingActors.Add(Actor, 0);
}

void ATimestepGameplayOptions::ResetActorsTickCounter(TArray<AActor*> AllActors)
{
    for(AActor* It : AllActors)
    {
        if(TickingActors.Contains(It))
            TickingActors[It] = 0;
    }
}

void ATimestepGameplayOptions::TickStepTimer(AActor* CheckActor, const int OnTick)
{

    if(TickingActors.Contains(CheckActor))
        TickingActors[CheckActor]++;

    
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
        if(Map.Value > OnTick)
            CheckTickedActors.Add(Map.Key);
    }
    
    ResetActorsTickCounter(CheckTickedActors);
    
    return CheckTickedActors;
}
