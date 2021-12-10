// Copyright 2017-2019 Vanny Sou. All Rights Reserved.

#include "Match3GameMode.h"
#include "POdimhGameInstance.h"
#include "Entities/Game/POdimhGameState.h"
#include "Entities/Game/Modes/GameplayOptions/Gameplay.h"
#include "Entities/Game/Modes/GameplayOptions/GameplayRunModeBase.h"
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

void AMatch3GameMode::Save(USaveGame* DataPtr)
{
    // save current score
    if(UPOdimhSaveGame* Data = Cast<UPOdimhSaveGame>(DataPtr))
    {
        Data->CustomInt.Add("GameScore", GetCurrentScore());
        Data->CustomInt.Add("POdimhAwareness", GameState->AwarenessCounter);
        Data->CustomInt.Add("TurnCounter", GameState->TurnCounter);
    }
    
    if(Participants.Num() == 0) return;
    
    SaveParticipants(DataPtr);
}

const bool AMatch3GameMode::Load(USaveGame* DataPtr)
{
    if(UPOdimhSaveGame* Data = Cast<UPOdimhSaveGame>(DataPtr))
    {
        SetCurrentScore(Data->CustomInt["GameScore"]);
        GameState->AwarenessCounter = Data->CustomInt["POdimhAwareness"];
        GameState->TurnCounter = Data->CustomInt["TurnCounter"];
    }
    return true;
}

const bool AMatch3GameMode::LoadParticipants(USaveGame* Data)
{
    // load from save
    if(UPOdimhSaveGame* SaveData = Cast<UPOdimhSaveGame>(Data))
    {
        GameState->ParticipantIndex = SaveData->CustomInt["CurrentParticipantIndex"];
        
        if(Participants.Num() > 0)
            return true;
        
        if(SaveData->ParticipantsRegistry.Num() != 0)
        {
            for(int32 i = 0; i < SaveData->ParticipantsRegistry.Num(); ++i)
            {
                FActorSpawnParameters Params;
                
                Params.Name = FName(*SaveData->ParticipantsRegistry[i].Id);
                Params.Owner = this;
                
                uint32 TurnNum = SaveData->ParticipantsRegistry[i].Value;
                
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
    if(GameState->bGameHasStarted)
        GameState->CurrentScore += Score;
}

const int AMatch3GameMode::GetCurrentScore()
{
    return GameState->CurrentScore;
}

void AMatch3GameMode::SetCurrentScore(const int32 Score)
{
    GameState->CurrentScore = Score;
}

void AMatch3GameMode::BeginPlay()
{
    Super::BeginPlay();

    GameState = GetGameState<APOdimhGameState>();
    UEventManager* EvtManager = Cast<UPOdimhGameInstance>(GetGameInstance())->EventManager;

    EvtManager->OnActorPicked.AddUniqueDynamic(this, &AMatch3GameMode::ReceiveActorPickedNotification);
    EvtManager->OnActorReleased.AddUniqueDynamic(this, &AMatch3GameMode::ReceiveActorReleasedNotification);

    if(RunMode)
        Mode = GetWorld()->SpawnActor<AGameplayRunModeBase>(RunMode);
    else
        Mode = GetWorld()->SpawnActor<AGameplayRunModeBase>();

    for(TSubclassOf<AGameplay> Class : GameplayOptions)
    {
        Gameplay.Add(GetWorld()->SpawnActor<AActor>(Class));
    }
}

void AMatch3GameMode::StartPlay()
{
    Super::StartPlay();
    
    // initialize
    for(AActor* Option : Gameplay)
    {
        if(IGameplayOptionsInterface* ImplementsGameplay = Cast<IGameplayOptionsInterface>(Option))
        {
            const uint32 StepsBeforeTick = Mode->GetTickCounter();
            const FGameStats Steps(StepsBeforeTick);
            
            Mode->AddGameplayToTick(Option, Steps);
        }
    }
    
    GetWorldTimerManager().SetTimer(GameStartTimerHandler, this, &AMatch3GameMode::StartGame, 1.f, true);
}

void AMatch3GameMode::StartMatch()
{
    Super::StartMatch();
    
    
}

void AMatch3GameMode::NotifyGameplayOptionsTurnEnding(const int OnTick)
{
    // call to whoever is concerned with the turn ending
    for(AActor* It : Gameplay)
        Cast<UPOdimhGameInstance>(GetGameInstance())->EventManager->CallbackOnCount.Broadcast(It, OnTick);
}

void AMatch3GameMode::SaveAndQuit(const int32 PlayerIndex)
{
    const bool bIgnorePlatformSpecificRestrictions = true;
    const bool bNotNewGame = false;
    
    GetGameInstance<UPOdimhGameInstance>()->SaveGame(CONTINUE_GAME_SLOT, PlayerIndex);
    
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
        SaveData->CustomInt.Add("CurrentParticipantIndex", GameState->ParticipantIndex);
        
        // loop and cycle through for each element
//        for(int i = 0; i < Participants.Num(); i++)
        for(auto& Elem : Participants)
        {
            if(AParticipantTurn* CurrentEntity = Elem.Value)
            {
                FCustomIntData NewInfo(CurrentEntity->GetDisplayName(),
                                                     Elem.Key);
                
                // add to save data
                SaveData->ParticipantsRegistry.Add(NewInfo);
#if !UE_BUILD_SHIPPING
                EntitiesRecorded++;
                UE_LOG(LogTemp,Warning,TEXT("Saving Participant: %s, QUEUE POSITION: %i"), *NewInfo.Id, NewInfo.Value);
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

UGameEvent* AMatch3GameMode::NewTurn(const FName& TurnDescription, const bool bStartTurnNow)
{
    UGameEvent* Turn = NewObject<UGameEvent>(GetGrid()->GetController(), TurnDescription);
    Turn->Init();
    if(bStartTurnNow)
        Turn->Start();
    return Turn;
}

void AMatch3GameMode::StartGame()
{
    if(AGrid* ActiveGame = GetGrid())
    {
        const int32 Player1 = (int32)EPlayer::One;
        
        if(!TryLoadGame(CONTINUE_GAME_SLOT, Player1))
        {
            if(!TryLoadGame(LAST_SUCCESSFUL_SLOT, Player1))
                ActiveGame->NewGrid();
        }
        PlayerMove = NewTurn("Player Move", true);
        GetWorldTimerManager().ClearTimer(GameStartTimerHandler);
        GameState->StartState = NewObject<UGameEvent>(ActiveGame->GetController(), "StartState");
        GameState->StartState->Init();
    }
    
}

void AMatch3GameMode::OnStartGame_Implementation(const bool bSaveGame)
{
    GameState->bGameHasStarted = true;
    UPOdimhGameInstance* Instance = GetGameInstance<UPOdimhGameInstance>();
    
    if(bSaveGame)
    {
        const int32 Player1 = (int32)EPlayer::One;
        
        Instance->SaveGame(RESET_GAME_SLOT, Player1);
        Instance->SaveGame(CONTINUE_GAME_SLOT, Player1);
        Instance->SaveGame(LAST_SUCCESSFUL_SLOT, Player1);
    }
    
    GameState->StartState->Start();
    Instance->EventManager->OnActorEvent.Broadcast(this, GameState->StartState);
}

const bool AMatch3GameMode::HasGameStarted() const
{
    return GameState->bGameHasStarted;
}

void AMatch3GameMode::ReceiveRequestToEndTurn()
{
    if(PlayerMove->IsPendingFinish())
        return;
    
    const int EndedOnTurnNum = GameState->TurnCounter;
    
    NotifyGameplayOptionsTurnEnding(EndedOnTurnNum);
    GetWorldTimerManager().SetTimer(TurnTickTimerHandler, this, &AMatch3GameMode::TryEndTurn, 1.f, true, 0.f);
}

void AMatch3GameMode::ReceiveRequestToEndTurn(ATile* LastTileGrabbed)
{
    ReceiveRequestToEndTurn();
}

void AMatch3GameMode::TryEndTurn()
{
    if(PendingGameplayFinish())
        return;
    
    UPOdimhGameInstance* Instance = GetGameInstance<UPOdimhGameInstance>();
    GameState->TurnCounter++;
    SaveCurrentGameState(Instance);
    Instance->EventManager->ClearEventQueue();
    PlayerMove->Reset();
    PlayerMove->Start();
    GetWorldTimerManager().ClearTimer(TurnTickTimerHandler);
}

void AMatch3GameMode::SaveCurrentGameState(UPOdimhGameInstance* Instance)
{
    const bool bNewGame = true;
    
    if(Instance->SafeToSave(!bNewGame))
    {
        Instance->SaveGame(CONTINUE_GAME_SLOT, (int32)EPlayer::One);
        Instance->SaveGame(LAST_SUCCESSFUL_SLOT, (int32)EPlayer::One);
    }
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

void AMatch3GameMode::ReceiveActorPickedNotification(AActor* PickedActor)
{
    if(ATile* Tile = Cast<ATile>(PickedActor))
    {
        FMatch3GameAction SwapAction;
        SwapAction.GameMode = this;
        SwapAction.Identifier = SWAP_POSITIONS;
        SwapAction.Num = INIT_MAX_ACTIONS;
        
        Give(GetGrid()->GetController(), SwapAction);
    }
}

void AMatch3GameMode::ReceiveActorReleasedNotification(AActor* ReleasedActor)
{
    if(ATile* Tile = Cast<ATile>(ReleasedActor))
    {
        ReceiveRequestToEndTurn(Tile);
        PlayerMove->End();
    }
}

const bool AMatch3GameMode::PendingGameplayFinish() const
{
    for(AActor* Option : Gameplay)
    {
        if(Cast<IGameplayOptionsInterface>(Option)->Execute_IsRunning(Option))
            return true;
    }
    return false;
}
