// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "POdimhGameInstance.h"
#include "POdimhSaveGame.h"
#include "EngineUtils.h"
#include "Gametypes.h"
#include "Events/GridEvent.h"
#include "Events/PlayerInputEvent.h"
#include "ClassInterface/DataSaveInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Events/EventManager.h"
#include "Events/BaseEvent.h"



UPOdimhGameInstance::UPOdimhGameInstance(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

void UPOdimhGameInstance::Init()
{
    Super::Init();
    EventManager = NewObject<UEventManager>();
}

UPOdimhSaveGame* UPOdimhGameInstance::CreateSaveGameObject()
{
    return Cast<UPOdimhSaveGame>(UGameplayStatics::CreateSaveGameObject(UPOdimhSaveGame::StaticClass()));
}

void UPOdimhGameInstance::SaveGameToSlot(USaveGame* Data, const FString& SlotName, const int32 Player)
{
    UGameplayStatics::SaveGameToSlot(Data, SlotName, Player);
}

void UPOdimhGameInstance::ResetGame(const int32 PlayerIndex)
{
    const bool bNotNewGame = false;
    LoadGame(RESET_GAME_SLOT,PlayerIndex);
    SaveGame(CONTINUE_GAME_SLOT,PlayerIndex, bNotNewGame);
}

void UPOdimhGameInstance::SaveGame(const FString& SlotName, const int32 PlayerIndex, const bool bNewGameState)
{
    if(!SafeToSave(bNewGameState))
        return;
    
    UPOdimhSaveGame* Data = CreateSaveGameObject();
    Data->SaveSlotName = SlotName;
    Data->UserIndex = PlayerIndex;
    
    for(TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
    {
        if(IDataSaveInterface* ActorSaveInterface = Cast<IDataSaveInterface>(*ActorItr))
        {
            ActorSaveInterface->NotifySave(Data);
            UGameplayStatics::SaveGameToSlot(Data, Data->SaveSlotName, Data->UserIndex);
        }
    }
    UE_LOG(LogTemp,Warning,TEXT("Saved to slot - %s"), *Data->SaveSlotName);
}

void UPOdimhGameInstance::LoadGame(const FString& SlotName, const int32 PlayerIndex)
{
    if(!UGameplayStatics::DoesSaveGameExist(SlotName, PlayerIndex))
        return;
    
    // init a new save game object
    UPOdimhSaveGame* Data = CreateSaveGameObject();
    
    // load game from slot
    Data = Cast<UPOdimhSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, PlayerIndex));
    
    for(TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
    {
        LoadActor(*ActorItr, Data);
        LoadComponents(*ActorItr, Data);
     }
}

const bool UPOdimhGameInstance::SafeToSave(const bool bNewGameState) const
{
    const bool bGameStateSafe = (EventManager->HasA(UGridEvent::StaticClass()) || bNewGameState);
    bool bNoPendingInput = true;
    
    TArray<UBaseEvent*> Events = EventManager->FindAll(UPlayerInputEvent::StaticClass());

    for(auto PlayerInput : Events)
    {
        if(PlayerInput->IsPendingFinish())
        {
            bNoPendingInput = false;
            break;
        }
    }
    
    return (bGameStateSafe && bNoPendingInput);
}

void UPOdimhGameInstance::LoadActor(AActor* Actor, USaveGame* Data)
{
    if(IDataSaveInterface* ActorSaveInterface = Cast<IDataSaveInterface>(Actor))
    {
        if(ActorSaveInterface->NotifyLoad(Data))
        {
            UE_LOG(LogTemp, Warning, TEXT("LoadActor: %s data loaded successfully.."), *ActorSaveInterface->_getUObject()->GetName());
        }
    }
}

void UPOdimhGameInstance::LoadComponents(AActor* Actor, USaveGame* Data)
{
    TInlineComponentArray<UActorComponent*> Components;
    Actor->GetComponents(Components);
    
    for(UActorComponent* Comp : Components)
    {
        if(IDataSaveInterface* LoadingInterface = Cast<IDataSaveInterface>(Comp))
        {
            if(LoadingInterface->NotifyLoad(Data))
            {
                UE_LOG(LogTemp, Warning, TEXT("LoadComponent: %s data loaded successfully.."), *LoadingInterface->_getUObject()->GetName());
            }
        }
    }
}

