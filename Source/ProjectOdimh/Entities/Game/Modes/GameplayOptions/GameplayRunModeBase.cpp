// Copyright 2017-2021 Vanny Sou. All Rights Reserved.


#include "GameplayRunModeBase.h"
#include "POdimhGameInstance.h"
#include "ClassInterface/GameplayOptionsInterface.h"
#include "Entities/Game/Modes/GameplayOptions/Gameplay.h"

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
        for(auto& Map : TickingGameplays)
        {
            const FString& OrigValStr = *Map.Key->GetName() + FString("Default");
            const FString& CurrValStr = *Map.Key->GetName() + FString("Value");
            
            POdimhData->CustomInt.Add(OrigValStr, Map.Value.Default);
            POdimhData->CustomInt.Add(CurrValStr, Map.Value.Value);
        }
    }
}

const bool AGameplayRunModeBase::Load(USaveGame* Data)
{
    if(UPOdimhSaveGame* POdimhData = Cast<UPOdimhSaveGame>(Data))
    {
        for(auto& Map: TickingGameplays)
        {
            const FString& OrigValStr = *Map.Key->GetName() + FString("Default");
            const FString& CurrValStr = *Map.Key->GetName() + FString("Value");
            
            Map.Value.Default = *POdimhData->CustomInt.Find(OrigValStr);
            Map.Value.Value = *POdimhData->CustomInt.Find(CurrValStr);
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
    EvtMgr->CallbackOnCount.AddDynamic(this, &AGameplayRunModeBase::StepTick);
}

const int AGameplayRunModeBase::GetOnTickFrom(AActor* Gameplay)
{
    int OnTick = -1;
    if(TickingGameplays.Contains(Gameplay))
        OnTick = TickingGameplays[Gameplay].Value;
    return OnTick;
}

void AGameplayRunModeBase::SetGameplayToTickOn(AActor* Gameplay, const FGameStats& TickOn)
{
    if(Gameplay == nullptr) return;
    
    if(AGameplay* ImplementsGameplay = Cast<AGameplay>(Gameplay))
    {
        if(TickingGameplays.Contains(Gameplay))
            ImplementsGameplay->SetNumTicksBeforeRun(TickOn.Default);
        else
            TickingGameplays.Add(Gameplay, TickOn);
    }
}

void AGameplayRunModeBase::StepTick(AActor* ActPtr, const int OnTick)
{
    if(TickingGameplays.Num() > 0)
    {
        if(ShouldTick(ActPtr, OnTick))
        {
            if(IGameplayOptionsInterface* TickGameplay = Cast<IGameplayOptionsInterface>(ActPtr))
                TickGameplay->Execute_Run(ActPtr);
        }
    }
}

const int AGameplayRunModeBase::GetTurnNumBeforeRun(AActor* CheckGameplay, const int CurrTurn)
{
    const int TickOn = GetOnTickFrom(CheckGameplay);
    
    if(TickOn > 0)
    {
        int TurnsBeforeTick = CurrTurn;
        while(TurnsBeforeTick % TickOn != 0)
            TurnsBeforeTick++;
        
        return (TurnsBeforeTick - CurrTurn) + 1;
    }
    return TickOn;
}

const bool AGameplayRunModeBase::ShouldTick(AActor* CheckGameplay, const int OnTick)
{
    if(TickingGameplays.Contains(CheckGameplay))
        return TickingGameplays[CheckGameplay].Value == 0 || OnTick % TickingGameplays[CheckGameplay].Value == 0;
    
    return false;
}

const TArray<AActor*> AGameplayRunModeBase::ShouldTick(const int OnTick)
{
    TArray<AActor*> CheckTickedGameplays;
    for(auto& Map : TickingGameplays)
    {
        if(Map.Value.Value == 0 || OnTick % Map.Value.Value == 0)
            CheckTickedGameplays.Add(Map.Key);
    }
    
    return CheckTickedGameplays;
}
