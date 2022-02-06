// Copyright 2022 Vanny Sou. All Rights Reserved.

#include "Match3GameMode.h"
#include "POdimhGameInstance.h"
#include "EngineUtils.h"
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
#include "Data/Tier.h"
#include "Entities/Controllers/Player/GridPlayerController.h"

AMatch3GameMode::AMatch3GameMode()
{
    PrimaryActorTick.bCanEverTick = false;
    
}

void AMatch3GameMode::BeginPlay()
{
    Super::BeginPlay();

    GameState = GetGameState<APOdimhGameState>();
    UEventManager* EvtManager = Cast<UPOdimhGameInstance>(GetGameInstance())->EventManager;

    EvtManager->OnActorPicked.AddUniqueDynamic(this, &AMatch3GameMode::ReceiveActorPickedNotification);
    EvtManager->OnActorReleased.AddUniqueDynamic(this, &AMatch3GameMode::ReceiveActorReleasedNotification);
    EvtManager->OnActorEvent.AddUniqueDynamic(this, &AMatch3GameMode::HandleTierThreshold);
    EvtManager->OnActorEvent.AddUniqueDynamic(this, &AMatch3GameMode::OnTurnEnd);
    
    LastMove = nullptr;
    
    if(RunMode)
        Mode = GetWorld()->SpawnActor<AGameplayRunModeBase>(RunMode);
    else
        Mode = GetWorld()->SpawnActor<AGameplayRunModeBase>();

    for(TSubclassOf<AGameplay> Class : GameplayOptions)
    {
        Gameplays.Add(GetWorld()->SpawnActor<AGameplay>(Class));
    }
}

void AMatch3GameMode::StartPlay()
{
    Super::StartPlay();
    
    // initialize
    for(AGameplay* Option : Gameplays)
    {
        if(IGameplayOptionsInterface* ImplementsGameplay = Cast<IGameplayOptionsInterface>(Option))
        {
            const uint32 StepsBeforeTick = Option->GetNumOfTicksBeforeRun();
            const FGameStats Steps(StepsBeforeTick);
            
            Mode->SetGameplayToTickOn(Option, Steps);
        }
    }
    
    GetWorldTimerManager().SetTimer(GameStartTimerHandler, this, &AMatch3GameMode::StartGame, 1.f, true);
}

void AMatch3GameMode::Save(USaveGame* DataPtr)
{
    // save current score
    if(UPOdimhSaveGame* Data = Cast<UPOdimhSaveGame>(DataPtr))
    {
        Data->CustomInt.Add("GameScore", GetCurrentScore());
        Data->CustomInt.Add("POdimhAwareness", GameState->AwarenessCounter);
        Data->CustomInt.Add("TurnCounter", GameState->TurnCounter);
        Data->CustomInt.Add("LifetimeMatchedTiles", GameState->LifetimeMatchedTiles);
        
        Data->CustomInt.Add("TierLevel", GameState->TierProgression->GetLevel());
        Data->CustomInt.Add("TierThresholdCurVal", GameState->TierProgression->GetTotalPoints());
        Data->CustomInt.Add("TierThresholdNeeded", GameState->TierProgression->GetThreshold());
    }
    
    if(ParticipantsList.Num() == 0) return;
    
    SaveParticipants(DataPtr);
}

const bool AMatch3GameMode::Load(USaveGame* DataPtr)
{
    if(UPOdimhSaveGame* Data = Cast<UPOdimhSaveGame>(DataPtr))
    {
        GameState->Score->Set((Data->CustomInt["GameScore"]));
        GameState->AwarenessCounter = Data->CustomInt["POdimhAwareness"];
        GameState->TurnCounter = Data->CustomInt["TurnCounter"];
        GameState->LifetimeMatchedTiles = Data->CustomInt["LifetimeMatchedTiles"];
        
        GameState->TierProgression->SetLevel
        (Data->CustomInt["TierLevel"],
        Data->CustomInt["TierThresholdCurVal"],
        Data->CustomInt["TierThresholdNeeded"]);
    }
    return true;
}

void AMatch3GameMode::StartMove(UGameEvent* PrevMove)
{
    if(LastMove == nullptr)
        LastMove = NewTurn("Begin", false);
    else if(PrevMove)
    {
        LastMove = PrevMove;
        LastMove->End();
    }
    
    if(IsPlayerTurn(GetGrid()->GetController()))
    {
        PlayerMove->Reset();
        PlayerMove->Start();
        GetGrid()->RegisterBoardState(TEXT("Pick"));
    }
}

void AMatch3GameMode::ResetLevel()
{
    Cast<UPOdimhGameInstance>(GetGameInstance())->EventManager->ClearEventQueue();
    
    // at the moment, AGameModeBase::ResetLevel will reset controller actors which
    // result in undesired behaviors with the game's puzzle grid.
    // instead only use a snippet of its code until a solution is found
    for (FActorIterator It(GetWorld()); It; ++It)
    {
        AActor* A = *It;
        if (A && !A->IsPendingKill() && A != this && !A->IsA<AController>() && ShouldReset(A))
        {
            A->Reset();
        }
    }
}

const bool AMatch3GameMode::LoadParticipants(USaveGame* Data)
{
    // load from save
    if(UPOdimhSaveGame* SaveData = Cast<UPOdimhSaveGame>(Data))
    {
        GameState->ParticipantIndex = SaveData->CustomInt["CurrentParticipantIndex"];
        
        if(ParticipantsList.Num() > 0)
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
                ParticipantsList.Add(TurnNum, NewEntity);
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
    return ParticipantsList;
}

const uint32 AMatch3GameMode::CalculateTotalTileValue(const uint32 TileCnt, const uint32 Mltplr)
{
    return TileCnt * Mltplr * TileValue;
}

void AMatch3GameMode::UpdateGameState(const int32 TileCnt, const int32 CmbCnt)
{
    if(GameState->bGameHasStarted)
    {
        GameState->ScoreMultiplier = CmbCnt;
        uint32 TotScr = CalculateTotalTileValue(TileCnt, CmbCnt);
        GameState->Score->Add(TotScr);
        GameState->TierProgression->Add(TileCnt);
    }
}

const int AMatch3GameMode::GetCurrentScore()
{
    return GameState->Score->GetTotalPoints();
}

void AMatch3GameMode::StartMatch()
{
    Super::StartMatch();
    
    
}

void AMatch3GameMode::NotifyGameplayOptionsTurnEnding(const int OnTick)
{
    // call to whoever is concerned with the turn ending on this tick
    for(AActor* It : Gameplays)
        Cast<UPOdimhGameInstance>(GetGameInstance())->EventManager->OnTurn.Broadcast(It, OnTick);
    
    UE_LOG(LogTemp, Warning, TEXT("--> NotifyGameplayOptionsTurnEnding on TURN: %i"), OnTick);
}

void AMatch3GameMode::SaveAndQuit(const int32 PlayerIndex)
{
    const bool bIgnorePlatformSpecificRestrictions = false;
    
    GetGameInstance<UPOdimhGameInstance>()->SaveGame(CONTINUE_GAME_SLOT, PlayerIndex);
    
//    UKismetSystemLibrary::QuitGame(GetWorld(),
//                                   UGameplayStatics::GetPlayerController(GetWorld(),PlayerIndex),
//                                   EQuitPreference::Background,
//                                   bIgnorePlatformSpecificRestrictions);
}

const bool AMatch3GameMode::ParticipantsBlueprintIsValid()
{
    if(Participants.Num() == 0)
    {
        UE_LOG(LogTemp,Warning,TEXT("Participant's blueprint contains no element."));
        return false;
    }
    
    for(auto& Check : Participants)
    {
        AParticipantTurn* IsValid = Check.Value.GetDefaultObject();
        uint32 TurnOrder = Check.Key;
        
        if(IsValid && TurnOrder > 0)
            continue;
        else
        {
            UE_LOG(LogTemp,Warning,TEXT("Participant's blueprint contain invalid data. Ensure blueprint is assigned in GameMode and TurnOrder is greater than 0."));
            return false;
        }
    }
    
    return true;
}

const bool AMatch3GameMode::LoadParticipantsFromBlueprint()
{
    UE_LOG(LogTemp,Warning,TEXT("Creating a Participants list from preassigned blueprint."));

    for(auto& Elem : Participants)
    {
        if(AParticipantTurn* Spawn_BP = GetWorld()->SpawnActor<AParticipantTurn>(Elem.Value))
        {
            const FString& ClassName = Spawn_BP->GetName();
            Spawn_BP->Init(Spawn_BP->GetDisplayName());
            
#if !UE_BUILD_SHIPPING
            UE_LOG(LogTemp,Warning,TEXT("Creating new Participant: %s, %i"), *ClassName, Elem.Key);
#endif
            ParticipantsList.Add(Elem.Key, Spawn_BP);
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
        const int32 NumOfEntities = ParticipantsList.Num();
        SaveData->CustomInt.Add("CurrentParticipantIndex", GameState->ParticipantIndex);
        
        // loop and cycle through for each element
//        for(int i = 0; i < ParticipantsList.Num(); i++)
        for(auto& Elem : ParticipantsList)
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
        PlayerMove = NewTurn("Player Move", false);
        GetWorldTimerManager().ClearTimer(GameStartTimerHandler);
        GameState->StartState = NewObject<UGameEvent>(ActiveGame->GetController(), F_GAME_HAS_STARTED_EVENT);
        GameState->StartState->Init();
        
        if(!TryLoadGame(CONTINUE_GAME_SLOT, Player1))
        {
            if(!TryLoadGame(LAST_SUCCESSFUL_SLOT, Player1))
                ActiveGame->NewGrid();
        }
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
//    GetGrid()->RegisterBoardState(FName(TEXT("Pick")));
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
    
    const float Delay = GetGrid()->DELAY_BETWEEN_TILE_BURSTS;
    
    // don't notify if game hasn't started
    NotifyGameplayOptionsTurnEnding(EndedOnTurnNum);
    GetWorldTimerManager().SetTimer(TurnTickTimerHandler, this, &AMatch3GameMode::TryEndTurn, Delay, true, 0.f);
}

void AMatch3GameMode::ReceiveRequestToEndTurn(ATile* LastTileGrabbed)
{
    ReceiveRequestToEndTurn();
}

void AMatch3GameMode::HandleTierThreshold(AActor* TierPtr, UBaseEvent* Evt)
{
    if(ATier* TierProgress = Cast<ATier>(TierPtr))
    {
        if(Evt->GetFName() == F_THRESHOLD_EVENT)
        {
            const uint32 Reset = 0;
            TierProgress->LevelUp(Reset, ATier::DEFAULT_NEXT_TIER);
        }
    }
}

void AMatch3GameMode::TryEndTurn()
{
    if(PendingGameplayFinish())
        return;
    
    UE_LOG(LogTemp, Warning, TEXT("--> TryEndTurn"));
    
    UPOdimhGameInstance* Instance = GetGameInstance<UPOdimhGameInstance>();
    
    UBaseEvent* Event = Instance->EventManager->NewEvent<UGameEvent>(this, F_TURN_ENDING_EVENT, true);
    Instance->EventManager->OnActorEvent.Broadcast(this, Event);
    
    
    GetWorldTimerManager().ClearTimer(TurnTickTimerHandler);
}

const bool AMatch3GameMode::IsPlayerTurn(AController* InCon) const
{
    return Cast<AGridPlayerController>(InCon);
}

void AMatch3GameMode::OnTurnEnd_Implementation(AActor* EvtCaller, UBaseEvent* Event)
{
    UE_LOG(LogTemp, Warning, TEXT("--> AMatch3GameMode::OnTurnEnd_Implementation"));
    UPOdimhGameInstance* Instance = GetGameInstance<UPOdimhGameInstance>();
    
    GameState->TurnCounter++;
    GameState->ScoreMultiplier = 0;
    GameState->BonusPoints = 0;
    GameState->LifetimeMatchedTiles += GetGrid()->GetTotalMatchedThisTurn();
    
    SaveCurrentGameState(Instance, false);
//    Instance->EventManager->ClearEventQueue();
    
    GetGrid()->ResetAccumulatedMatchedTiles();
}

void AMatch3GameMode::SaveCurrentGameState(UPOdimhGameInstance* Instance, const bool bIsNewGame)
{
    if(Instance->SafeToSave(bIsNewGame))
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
    for(AActor* Option : Gameplays)
    {
        if(IGameplayOptionsInterface* Gameplay = Cast<IGameplayOptionsInterface>(Option))
        {
            if(Gameplay->Execute_IsRunning(Option))
                return true;
        }
    }
    return false;
}
