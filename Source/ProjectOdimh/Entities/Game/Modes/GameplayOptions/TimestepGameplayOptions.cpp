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
        for(auto& Map : GameplayTriggers)
            POdimhData->CustomInt.Add(*Map.Key->GetName(), Map.Value);
    }
}

const bool ATimestepGameplayOptions::NotifyLoad(USaveGame* Data)
{
    if(UPOdimhSaveGame* POdimhData = Cast<UPOdimhSaveGame>(Data))
    {
        for(auto& Map: GameplayTriggers)
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
    EvtMgr->CallBack.AddDynamic(this, &ATimestepGameplayOptions::TickStepTimer);
}

const int ATimestepGameplayOptions::GetStepTimer(AActor* GameplayOption)
{
    int StepTimer = -1;
    if(GameplayTriggers.Contains(GameplayOption))
        StepTimer = GameplayTriggers[GameplayOption];
    return StepTimer;
}

void ATimestepGameplayOptions::AddActorToTrigger(AActor* Actor)
{
    GameplayTriggers.Add(Actor, 0);
}

void ATimestepGameplayOptions::ResetTimer(TArray<AActor*> AllActors)
{
    for(AActor* It : AllActors)
    {
        if(GameplayTriggers.Contains(It))
            GameplayTriggers[It] = 0;
    }
}

void ATimestepGameplayOptions::TickStepTimer(AActor* CheckActor)
{

    if(GameplayTriggers.Contains(CheckActor))
        GameplayTriggers[CheckActor]++;

    
    for(AActor* It : ShouldTrigger(RunGameplayOnTargetCounter))
    {
        if(IGameplayOptionsInterface* TimerTriggeredActor= Cast<IGameplayOptionsInterface>(It))
            TimerTriggeredActor->Run(true);
    }
}

const TArray<AActor*> ATimestepGameplayOptions::ShouldTrigger(const int Check)
{
    TArray<AActor*> CheckedActors;
    for(auto& Map : GameplayTriggers)
    {
        if(Map.Value > Check)
            CheckedActors.Add(Map.Key);
    }
    
    ResetTimer(CheckedActors);
    
    return CheckedActors;
}
