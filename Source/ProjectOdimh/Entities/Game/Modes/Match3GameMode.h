// Copyright 2017-2019 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Data/Gametypes.h"
#include "ClassInterface/DataSaveInterface.h"
#include "Match3GameMode.generated.h"

const int8 INIT_BASE_SCORE_MULTIPLIER = 1;

class AGrid;
class ATile;
class UGameEvent;
class AParticipantTurn;
class ATimestepGameplayOptions;

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
    
    void NotifyGameplayOptionsTurnEnding(const int TurnNum);
    
    /** Save the game and quit */
    UFUNCTION(BlueprintCallable)
    void SaveAndQuit(const int32 PlayerIndex);
    
    /** Add to the score */
    UFUNCTION(BlueprintCallable)
    void AddScore(const int32 Score);
    
    /** Get the current score of the game */
    UFUNCTION(BlueprintPure)
    const int GetCurrentScore();
    
    void SetCurrentScore(const int32 Score);
    
    const bool TryLoadGame(const FString &SlotName, const int32 PlayerIndex);
    
    UFUNCTION()
    void StartGame();
    
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void OnStartGame(const bool bSaveGame);
    
    const bool HasGameStarted() const;
    
    UGameEvent* NewTurn(const FName& TurnDescription, const bool bStartTurnNow);
    
    UFUNCTION(BlueprintImplementableEvent)
    void OnTurnStart(const FString& ParticipantName);
    
    void ReceiveRequestToEndTurn();
    void ReceiveRequestToEndTurn(ATile* LastTileGrabbed);
    
    void TryEndTurn();
    
    UFUNCTION(BlueprintCallable)
    void SaveCurrentGameState(UPOdimhGameInstance* Instance);
    
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
    
    UPROPERTY(EditAnywhere, Category="Additional Gameplay")
    TSubclassOf<ATimestepGameplayOptions> TimerClass;
    
    UPROPERTY(EditAnywhere, Category="Additional Gameplay")
    TArray<TSubclassOf<AActor>> GameplayOptionsClass;
    
    UPROPERTY(BlueprintReadOnly)
    ATimestepGameplayOptions* TimerPtr;
    
    UPROPERTY(BlueprintReadOnly)
    TArray<AActor*> GameplayOptions;
    
    class APOdimhGameState* PGameState;
    
private:
    UPROPERTY()
    UGameEvent* PlayerMove;
    
    FTimerHandle TimerHandler;
    
    // deprecate
    AParticipantTurn* NewParticipant(const FActorSpawnParameters& Params);
    const bool ParticipantsBlueprintIsValid();
    const bool LoadParticipantsFromBlueprint();
    const bool LoadParticipants(USaveGame* Data);
    void SaveParticipants(USaveGame* Data);
    
    TMap<uint32, AParticipantTurn*>& GetParticipants();
    
    UPROPERTY(EditAnywhere)
    TMap<uint32, TSubclassOf<AParticipantTurn>> ParticipantsBlueprint;
    
    UPROPERTY()
    TMap<uint32, AParticipantTurn*> Participants;

    
};
