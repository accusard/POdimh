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
class PROJECTODIMH_API AMatch3GameMode : public AGameModeBase, public IDataSaveInterface
{
	GENERATED_BODY()
	
public:
    // constructor
    AMatch3GameMode();

    virtual void StartPlay() override;
    virtual void NotifySave(USaveGame* Data) override;
    virtual const bool NotifyLoad(USaveGame* Data) override;
    
    void NotifyGameplayOptionsTurnEnded(const int TurnNum);
    
    /** Save the game and quit */
    UFUNCTION(BlueprintCallable)
    void SaveAndQuit(const int32 PlayerIndex);

    const bool ParticipantsBlueprintIsValid();
    
    const bool LoadParticipantsFromBlueprint();
    
    const bool LoadParticipants(USaveGame* Data);
    
    void SaveParticipants(USaveGame* Data);
    
    TMap<uint32, AParticipantTurn*>& GetParticipants();
    
    /** Add to the score */
    UFUNCTION(BlueprintCallable)
    void AddScore(const int32 Score);
    
    /** Get the current score of the game */
    UFUNCTION(BlueprintPure)
    const int GetCurrentScore();
    
    void SetCurrentScore(const int32 Score);
    
    const bool TryLoadGame(const FString &SlotName, const int32 PlayerIndex);
    
    const bool NewGame();
    
    UFUNCTION(BlueprintCallable)
    void StartGame(const bool bIsNewGame);
    
    AParticipantTurn* StartNextParticipant(const uint32 ParticipantTurnNum);
    
    UFUNCTION(BlueprintImplementableEvent)
    void OnRoundStart();
    
    UFUNCTION(BlueprintImplementableEvent)
    void OnTurnStart(const FString& ParticipantName);
    
    UFUNCTION(BlueprintImplementableEvent)
    void OnRoundEnd();
    
    void ReceiveRequestToEndTurn();
    void ReceiveRequestToEndTurn(ATile* LastTileGrabbed);
    
    UFUNCTION(BlueprintCallable, Category="")
    AParticipantTurn* GetCurrentParticipant() const;
    
    AParticipantTurn* NewParticipant(const FActorSpawnParameters& Params);
    
    void Give(AActor* Controller, const FMatch3GameAction& Action, const bool bExecuteNow = true);
    
    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
    AGrid* GetGrid() const;
    
    const bool StartTurn(const uint32 Index, APawn* InPawn);
    
    UFUNCTION()
    void ReceiveActorReleasedNotification(AActor* Actor);
    
    UFUNCTION()
    void ReceiveActorPickedNotification(AActor* PickedActor);
    
    const bool IsTurnPending() const;
    
protected:
    virtual void BeginPlay() override;
    
    UPROPERTY(EditAnywhere)
    TMap<uint32, TSubclassOf<AParticipantTurn>> ParticipantsBlueprint;
    
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
    void StartTurn(AParticipantTurn* Turn, APawn* InPawn);
    
    UPROPERTY()
    TMap<uint32, AParticipantTurn*> Participants;
    
    AParticipantTurn* CurrentParticipant;
    
    UGameEvent* ActiveTurn;
    
};
