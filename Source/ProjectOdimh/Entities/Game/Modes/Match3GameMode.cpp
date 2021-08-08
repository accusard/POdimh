// Copyright 2017-2019 Vanny Sou. All Rights Reserved.

#include "Match3GameMode.h"
#include "POdimhGameInstance.h"
#include "Entities/Game/POdimhGameState.h"
//#include "Entities/Game/Modes/GameplayOptions/RelayLine.h"
#include "Entities/Game/Modes/GameplayOptions/TimestepGameplayOptions.h"
#include "ClassInterface/GameplayOptionsInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Entities/Game/ParticipantTurn.h"
#include "Entities/Game/Grid.h"
#include "Components/ActionTurnBasedComponent.h"
#include "Events/GameEvent.h"
#include "Events/EventManager.h"



AMatch3GameMode::AMatch3GameMode()
{
    PrimaryActorTick.bCanEverTick = false;
    
}

void AMatch3GameMode::NotifySave(USaveGame* DataPtr)
{
    // save current score
    if(UPOdimhSaveGame* Data = Cast<UPOdimhSaveGame>(DataPtr))
        Data->SavedGrid.GameScore = GetCurrentScore();
    
    if(Participants.Num() == 0) return;
    
    SaveParticipants(DataPtr);
}

const bool AMatch3GameMode::NotifyLoad(USaveGame* DataPtr)
{
    if(UPOdimhSaveGame* Data = Cast<UPOdimhSaveGame>(DataPtr))
        SetCurrentScore(Data->SavedGrid.GameScore);
    
    return LoadParticipants(DataPtr);
}

const bool AMatch3GameMode::LoadParticipants(USaveGame* Data)
{
    // load from save
    if(UPOdimhSaveGame* SaveData = Cast<UPOdimhSaveGame>(Data))
    {
        PGameState->ParticipantIndex = SaveData->CurrentParticipantIndex;
        
        if(Participants.Num() > 0)
            return true;
        
        if(SaveData->ParticipantsRegistry.Num() != 0)
        {
            for(int32 i = 0; i < SaveData->ParticipantsRegistry.Num(); ++i)
            {
                FActorSpawnParameters Params;
                
                Params.Name = FName(*SaveData->ParticipantsRegistry[i].Name);
                Params.Owner = this;
                
                uint32 TurnNum = SaveData->ParticipantsRegistry[i].PositionInQueue;
                
#if !UE_BUILD_SHIPPING
                UE_LOG(LogTemp,Warning,TEXT("Loading Participant: %s, Turn: %i"),*Params.Name.ToString(), TurnNum);
#endif
                AParticipantTurn* NewEntity = NewParticipant(Params);
                Participants.Add(TurnNum, NewEntity);
            }
            return true;
        }
    }
    return false;
}

AParticipantTurn* AMatch3GameMode::NewParticipant(const FActorSpawnParameters& Params)
{
    AParticipantTurn* NewEntity = GetWorld()->SpawnActor<AParticipantTurn>(AParticipantTurn::StaticClass(), Params);
    NewEntity->Init(*Params.Name.ToString());
    
    return NewEntity;
}

TMap<uint32, AParticipantTurn*>& AMatch3GameMode::GetParticipants()
{
    return Participants;
}

void AMatch3GameMode::AddScore(const int32 Score)
{
    if(PGameState->bEnableScoring)
        PGameState->CurrentScore += Score;
}

const int AMatch3GameMode::GetCurrentScore()
{
    return PGameState->CurrentScore;
}

void AMatch3GameMode::SetCurrentScore(const int32 Score)
{
    PGameState->CurrentScore = Score;
}

void AMatch3GameMode::BeginPlay()
{
    Super::BeginPlay();
    
    UEventManager* EvtManager = Cast<UPOdimhGameInstance>(GetGameInstance())->EventManager;
    
    EvtManager->OnActorPicked.AddUniqueDynamic(this, &AMatch3GameMode::ReceiveActorPickedNotification);
    EvtManager->OnActorReleased.AddUniqueDynamic(this, &AMatch3GameMode::ReceiveActorReleasedNotification);
    
    if(TimerClass)
           TimerPtr = GetWorld()->SpawnActor<ATimestepGameplayOptions>(TimerClass);
    
    for(TSubclassOf<AActor> Class : GameplayOptionsClass)
    {
        GameplayOptions.Add(GetWorld()->SpawnActor<AActor>(Class));
    }
}

void AMatch3GameMode::StartPlay()
{
    Super::StartPlay();
    
    // initialize
    for(AActor* Option : GameplayOptions)
    {
        if(IGameplayOptionsInterface* ImplmentsGameplay = Cast<IGameplayOptionsInterface>(Option))
        {
            const uint32 StepsBeforeTick = TimerPtr->GetDefaultStepsBeforeTick();
            const FGameStats Steps(StepsBeforeTick);
            
            TimerPtr->AddActorToTick(Option, Steps);
        }
    }
    
    bool bIsNewGame = false;
    const int32 Player1 = (int32)EPlayer::One;
    PGameState = GetGameState<APOdimhGameState>();
    
    
    if(!TryLoadGame(CONTINUE_GAME_SLOT, Player1))
    {
        if(!TryLoadGame(LAST_SUCCESSFUL_SLOT, Player1))
            bIsNewGame = NewGame();
    }
}

void AMatch3GameMode::NotifyGameplayOptionsTurnEnded(const int OnTick)
{
    for(AActor* It : GameplayOptions)
        Cast<UPOdimhGameInstance>(GetGameInstance())->EventManager->CallBackOnStepTick.Broadcast(It, OnTick);
}

void AMatch3GameMode::SaveAndQuit(const int32 PlayerIndex)
{
    const bool bIgnorePlatformSpecificRestrictions = true;
    const bool bNotNewGame = false;
    
    GetGameInstance<UPOdimhGameInstance>()->SaveGame(CONTINUE_GAME_SLOT, PlayerIndex, bNotNewGame);
    
    UKismetSystemLibrary::QuitGame(GetWorld(),
                                   UGameplayStatics::GetPlayerController(GetWorld(),PlayerIndex),
                                   EQuitPreference::Quit,
                                   bIgnorePlatformSpecificRestrictions);
}

const bool AMatch3GameMode::ParticipantsBlueprintIsValid()
{
    if(ParticipantsBlueprint.Num() == 0)
    {
        UE_LOG(LogTemp,Warning,TEXT("ParticipantsBlueprint contain no element."));
        return false;
    }
    
    for(auto& Check : ParticipantsBlueprint)
    {
        AParticipantTurn* IsValid = Check.Value.GetDefaultObject();
        uint32 TurnOrder = Check.Key;
        
        if(IsValid && TurnOrder > 0)
            continue;
        else
        {
            UE_LOG(LogTemp,Warning,TEXT("ParticipantsBlueprint contain invalid data. Ensure blueprint is assigned in GameMode and TurnOrder is greater than 0."));
            return false;
        }
    }
    
    return true;
}

const bool AMatch3GameMode::LoadParticipantsFromBlueprint()
{
    UE_LOG(LogTemp,Warning,TEXT("Creating a Participants list from preassigned blueprint."));

    for(auto& Elem : ParticipantsBlueprint)
    {
        if(AParticipantTurn* Spawn_BP = GetWorld()->SpawnActor<AParticipantTurn>(Elem.Value))
        {
            const FString& ClassName = Spawn_BP->GetName();
            Spawn_BP->Init(Spawn_BP->GetDisplayName());
            
#if !UE_BUILD_SHIPPING
            UE_LOG(LogTemp,Warning,TEXT("Creating new Participant: %s, %i"), *ClassName, Elem.Key);
#endif
            Participants.Add(Elem.Key, Spawn_BP);
        }
        else
        {
            UE_LOG(LogTemp,Warning,TEXT("Failed to load Participants from blueprint."))
            return false;
        }
    }
        
    return true;
}

void AMatch3GameMode::SaveParticipants(USaveGame* DataPtr)
{
#if !UE_BUILD_SHIPPING
    uint32 EntitiesRecorded = 0;
#endif
    if(UPOdimhSaveGame* SaveData = Cast<UPOdimhSaveGame>(DataPtr))
    {
        const int32 NumOfEntities = Participants.Num();
        SaveData->CurrentParticipantIndex = PGameState->ParticipantIndex;
        
        // loop and cycle through for each element
//        for(int i = 0; i < Participants.Num(); i++)
        for(auto& Elem : Participants)
        {
            if(AParticipantTurn* CurrentEntity = Elem.Value)
            {
                FParticipantInfo NewInfo(CurrentEntity->GetDisplayName(),
                                                     Elem.Key);
                
                // add to save data
                SaveData->ParticipantsRegistry.Add(NewInfo);
#if !UE_BUILD_SHIPPING
                EntitiesRecorded++;
                UE_LOG(LogTemp,Warning,TEXT("Saving Participant: %s, QUEUE POSITION: %i"), *NewInfo.Name, NewInfo.PositionInQueue);
#endif
            }
            
        }
#if !UE_BUILD_SHIPPING
        UE_LOG(LogTemp,Warning,TEXT("Participants contain (%i) entities; data saved (%i) entities."), NumOfEntities, EntitiesRecorded);
        UE_LOG(LogTemp,Warning,TEXT(""));
#endif
    }
}

const bool AMatch3GameMode::TryLoadGame(const FString &SlotName, const int32 PlayerIndex)
{
    if(UGameplayStatics::DoesSaveGameExist(SlotName, PlayerIndex))
    {
        return GetGameInstance<UPOdimhGameInstance>()->LoadGame(SlotName, PlayerIndex);
    }
    
    return false;
}

const bool AMatch3GameMode::NewGame()
{
    if(ParticipantsBlueprintIsValid() && LoadParticipantsFromBlueprint())
    {
        PGameState->bEnableScoring = false;
        PGameState->TurnCounter = 0;
        PGameState->RoundCounter = 0;
        PGameState->ParticipantIndex = 1;
        GetGrid()->NewGrid();
        return true;
    }
    return false;
}

void AMatch3GameMode::StartGame(const bool bIsNewGame)
{
    PGameState->bEnableScoring = true;
    const int32 Player1 = (int32)EPlayer::One;
    
    if(Participants.Num() != 0)
    {
        const uint32 NextParticipant = PGameState->ParticipantIndex;

        StartNextParticipant(NextParticipant);
        if(bIsNewGame)
        {
            UPOdimhGameInstance* Instance = GetGameInstance<UPOdimhGameInstance>();
            Instance->SaveGame(RESET_GAME_SLOT, Player1, bIsNewGame);
            Instance->SaveGame(CONTINUE_GAME_SLOT, Player1, bIsNewGame);
            Instance->SaveGame(LAST_SUCCESSFUL_SLOT, Player1, bIsNewGame);
        }
    }
    else
        UE_LOG(LogTemp, Warning, TEXT("Error starting round. Participants contain 0 objects."));
}

AParticipantTurn* AMatch3GameMode::StartNextParticipant(const uint32 ParticipantTurnNum)
{
    CurrentParticipant = nullptr;
    
    if(AParticipantTurn* NextParticipant = Participants[ParticipantTurnNum])
    {
        PGameState->RoundCounter++;
        CurrentParticipant = NextParticipant;
        StartTurn(ParticipantTurnNum, nullptr);
        OnRoundStart();
    }
    
    return CurrentParticipant;
}

void AMatch3GameMode::ReceiveRequestToEndTurn()
{
    if(GetGrid()->IsTilesBursting() || IsTurnPending())
        return;
    
    if(AParticipantTurn* ActiveParticipant = GetCurrentParticipant())
    {
        if(AController* GridController = ActiveParticipant->GetGridController())
            GridController->UnPossess();
    }
    
    const bool bIsNewGame = true;
    const int EndedOnTurnNum = PGameState->TurnCounter;
    
    UPOdimhGameInstance* Instance = GetGameInstance<UPOdimhGameInstance>();
    Instance->SaveGame(CONTINUE_GAME_SLOT, (int32)EPlayer::One, !bIsNewGame);
    Instance->SaveGame(LAST_SUCCESSFUL_SLOT, (int32)EPlayer::One, !bIsNewGame);
    Instance->EventManager->ClearEventQueue();
    
    // Participants
    if(AParticipantTurn* ActiveParticipant = GetCurrentParticipant())
    {
        // next turn
        for(uint32 i = ++PGameState->ParticipantIndex; i <= Participants.Num(); ++i)
        {
            if(StartTurn(i, nullptr))
                return;
            else
                continue;
        }
        
        // end of round
        for(int i = 1; i <= Participants.Num(); i++)
        {
            if(AParticipantTurn* Participant = Cast<AParticipantTurn>(Participants[i]))
                Participant->Reset();
        }
    }
    
    ActiveTurn->End();
    NotifyGameplayOptionsTurnEnded(EndedOnTurnNum);
    OnRoundEnd();
    PGameState->ParticipantIndex = 1;
    StartTurn(PGameState->ParticipantIndex, nullptr);
}

void AMatch3GameMode::ReceiveRequestToEndTurn(ATile* LastTileGrabbed)
{
    if(AParticipantTurn* ActiveParticipant = GetCurrentParticipant())
    {
        if(GetGrid()->HasTilePositionChanged(LastTileGrabbed))
            ReceiveRequestToEndTurn();
    }
}

AParticipantTurn* AMatch3GameMode::GetCurrentParticipant() const
{
    if(ActiveTurn)
        return Cast<AParticipantTurn>(ActiveTurn->GetOwner());
    return nullptr;
}

void AMatch3GameMode::Give(AActor* Controller, const FMatch3GameAction& Action, const bool bExecuteNow)
{
    // give to the current active participant
    if(bExecuteNow && Controller)
    {
        if(UActionTurnBasedComponent* ActionComp = Controller->FindComponentByClass<UActionTurnBasedComponent>())
            ActionComp->TryExecute(Action);
    }
    
    // TODO: give to pending action?
}

const bool AMatch3GameMode::StartTurn(const uint32 Index, APawn* InPawn)
{
    if(Participants.Contains(Index))
    {
        PGameState->ParticipantIndex = Index;
        StartTurn(Participants[Index], InPawn);
        return true;
    }
    return false;
}

void AMatch3GameMode::StartTurn(AParticipantTurn* Participant, APawn* InPawn)
{
    if(Participant)
    {
        if(ActiveTurn && !ActiveTurn->IsPendingKill())
        {
            ActiveTurn->End();
            ActiveTurn->MarkPendingKill();
        }
        const bool bStartTurnNow = true;
        FString TurnDescription = Participant->GetDisplayName();
        TurnDescription.Append("'s Turn");
        
        ActiveTurn = GetGameInstance<UPOdimhGameInstance>()->EventManager->NewEvent<UGameEvent>(Participant, FName(*TurnDescription), bStartTurnNow);
        
        if(InPawn)
            Participant->GetGridController()->Possess(InPawn);
        else
            UE_LOG(LogTemp, Warning, TEXT("TODO: Need GridController and InPawn to possess."));
        
        PGameState->TurnCounter++;
        OnTurnStart(*Participant->GetDisplayName());
        
        UE_LOG(LogTemp, Warning, TEXT("DebugTurn: Starting Turn %i: %s."), PGameState->TurnCounter, *Participant->GetDisplayName());
    }
}

void AMatch3GameMode::ReceiveActorPickedNotification(AActor* PickedActor)
{
    if(ATile* Tile = Cast<ATile>(PickedActor))
    {
        FMatch3GameAction SwapAction;
        SwapAction.GameMode = this;
        SwapAction.Identifier = SWAP_POSITIONS;
        SwapAction.Num = INIT_MAX_ACTIONS;
        
        Give(GetCurrentParticipant()->GetGridController(), SwapAction);
    }
}

void AMatch3GameMode::ReceiveActorReleasedNotification(AActor* ReleasedActor)
{
    if(ActiveTurn)
    {
        if(ATile* Tile = Cast<ATile>(ReleasedActor))
        {
            ReceiveRequestToEndTurn(Tile);
            ActiveTurn->End();
        }
    }
}

const bool AMatch3GameMode::IsTurnPending() const
{
    if(ActiveTurn)
        return ActiveTurn->IsPendingFinish();
    else
        return false;
}
