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
        POdimhData->CustomInt.Add(TEXT("StepTimer"), Counter);
    }
}

const bool ATimestepGameplayOptions::NotifyLoad(USaveGame* Data)
{
    if(UPOdimhSaveGame* POdimhData = Cast<UPOdimhSaveGame>(Data))
    {
        if(POdimhData->CustomInt.Find(TEXT("StepTimer")))
        {
            Counter = POdimhData->CustomInt[TEXT("StepTimer")];
            return true;
        }
    }
    
    
    return false;
}

// Called when the game starts or when spawned
void ATimestepGameplayOptions::BeginPlay()
{
	Super::BeginPlay();
    
    ResetTimer();
    
    UEventManager* EvtMgr = Cast<UPOdimhGameInstance>(GetGameInstance())->EventManager;
    EvtMgr->TriggerGameplayOption.AddDynamic(this, &ATimestepGameplayOptions::TickStepTimer);
}

const int ATimestepGameplayOptions::GetStepTimer(AActor* GameplayOption)
{
    int StepTimer = -1;
    if(GameplayTriggers.Contains(GameplayOption))
        StepTimer = GameplayTriggers[GameplayOption];
    return StepTimer;
}

void ATimeStepGameplayOptions::AddActorToTrigger(AActor* Actor)
{
    GameplayTriggers.Add(Actor, 0);
}

void ATimestepGameplayOptions::ResetTimer(TArray<AActor*> AllActors)
{
    for(AActor* It : AllActors)
    {
        if(GameplayTriggers.Contains(It))
            GameplayTrigger[It] = 0;
    }
}

void ATimeStepGameplayOptions::TickStepTimer(AActor* CheckActor)
{

    if(GameplayTriggers.Contain(CheckActor))
        GameplayTriggers[CheckActor]++;

    
    for(AActor* It : ShouldTrigger())
    {
        if(IGameplayOptionsInterface* TimerTriggeredActor(It))
            TimerTriggeredActor->Run(true);
    }
}

TArray<AActor*> ATimeStepGameplayOptions::ShouldTrigger(const int Check) const
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
