// Copyright 2017-2019 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Data/Gametypes.h"
#include "ClassInterface/DataSaveInterface.h"
#include "Match3GameMode.generated.h"



class AGrid;
class ATile;
class UGameEvent;
class AParticipantTurn;
class AGameplayRunModeBase;

/**
 * The mode for a Match3 game. Tracks a turn-based puzzle game.
 */
UCLASS()
class PROJECTODIMH_API AMatch3GameMode : public AGameMode, public IDataSaveInterface
{
	GENERATED_BODY()
	
public:
    // constructor
    AMatch3GameMode();

    virtual void StartPlay() override;
    virtual void Save(USaveGame* Data) override;
    virtual const bool Load(USaveGame* Data) override;
    virtual void StartMatch() override;
    virtual void ResetLevel() override;
    
    void NotifyGameplayOptionsTurnEnding(const int TurnNum);
    
    /** Save the game and quit */
    UFUNCTION(BlueprintCallable)
    void SaveAndQuit(const int32 PlayerIndex);
    
    const uint32 CalculateTotalTileValue(const uint32 TileCount, const uint32 Multiplier = DEFAULT_SCORE_MULTIPLIER);
    
    /** Add to the score */
    UFUNCTION(BlueprintCallable)
    void UpdateGameState(const int32 TileCount, const int32 ComboCount);
    
    /** Get the current score of the game */
    UFUNCTION(BlueprintPure)
    const int GetCurrentScore();
    
    const bool TryLoadGame(const FString &SlotName, const int32 PlayerIndex);
    
    UFUNCTION(BlueprintCallable)
    void StartGame();
    
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void OnStartGame(const bool bSaveGame);
    
    UFUNCTION(BlueprintPure)
    const bool HasGameStarted() const;
    
    UGameEvent* NewTurn(const FName& TurnDescription, const bool bStartTurnNow);
    
    UFUNCTION(BlueprintImplementableEvent)
    void OnTurnStart(const FString& ParticipantName);
    
    void ReceiveRequestToEndTurn();
    void ReceiveRequestToEndTurn(ATile* LastTileGrabbed);
    
    UFUNCTION()
    void HandleTierThreshold(AActor* TierPtr, UBaseEvent* Evt);
    
    void TryEndTurn();
    
    UFUNCTION(BlueprintCallable)
    void SaveCurrentGameState(UPOdimhGameInstance* Instance, const bool bIsNewGame);
    
    void Give(AActor* Controller, const FMatch3GameAction& Action, const bool bExecuteNow = true);
    
    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
    AGrid* GetGrid() const;
    
    UFUNCTION()
    void ReceiveActorReleasedNotification(AActor* Actor);
    
    UFUNCTION()
    void ReceiveActorPickedNotification(AActor* PickedActor);
    
    const bool PendingGameplayFinish() const;
    
protected:
    virtual void BeginPlay() override;
    
    /** The gameplay mode to run when Match3GameMode receive request to end turn */
    UPROPERTY(EditAnywhere, Category="Additional Gameplay")
    TSubclassOf<AGameplayRunModeBase> RunMode;
    
    UPROPERTY(EditAnywhere, Category="Additional Gameplay")
    TArray<TSubclassOf<class AGameplay>> GameplayOptions;
    
    UPROPERTY(BlueprintReadOnly)
    AGameplayRunModeBase* Mode;
    
    UPROPERTY(BlueprintReadOnly)
    TArray<class AGameplay*> Gameplays;
    
    class APOdimhGameState* GameState;
    
private:
    UPROPERTY(EditDefaultsOnly)
    int32 TileValue = INIT_TILE_VALUE;
    
    UPROPERTY()
    UGameEvent* PlayerMove;
    
    FTimerHandle TurnTickTimerHandler;
    FTimerHandle GameStartTimerHandler;
    // deprecate
    AParticipantTurn* NewParticipant(const FActorSpawnParameters& Params);
    const bool ParticipantsBlueprintIsValid();
    const bool LoadParticipantsFromBlueprint();
    const bool LoadParticipants(USaveGame* Data);
    void SaveParticipants(USaveGame* Data);
    
    TMap<uint32, AParticipantTurn*>& GetParticipants();
    
    UPROPERTY(EditAnywhere, Category="Additional Gameplay")
    TMap<uint32, TSubclassOf<AParticipantTurn>> Participants;
    
    UPROPERTY()
    TMap<uint32, AParticipantTurn*> ParticipantsList;

    
};
