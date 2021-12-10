// Copyright 2017-2021 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ClassInterface/DataSaveInterface.h"
#include "Data/FGameStats.h"
#include "GameplayRunModeBase.generated.h"

UCLASS()
class PROJECTODIMH_API AGameplayRunModeBase : public AActor, public IDataSaveInterface 
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameplayRunModeBase();

    virtual void Save(USaveGame* Data) override;
    virtual const bool Load(USaveGame* Data) override;
    
    const int GetOnTickFrom(AActor* Gameplay);
    
    void AddGameplayToTick(AActor* Gameplay, const FGameStats& Tick);
    
    UFUNCTION(BlueprintCallable)
    void ResetGameplaysTickCounter(TArray<AActor*> Gameplays);
    
    UFUNCTION(BlueprintCallable)
    void SetGameplayToTickOn(AActor* SetGameplay, const int TickOn);
    
    UFUNCTION(BlueprintCallable)
    void ResetAllGameplaysTickCounter();
    
    UFUNCTION()
    void StepTick(AActor* Gameplay, const int OnTick);
    
    UFUNCTION(BlueprintPure)
    const int GetTurnNumBeforeTick(AActor* CheckGameplay, const int CurrentTurn);
    
    const bool ShouldTick(AActor* CheckGameplay, const int OnTick);
    const TArray<AActor*> ShouldTick(const int OnTick);
    
    const uint32 GetTickCounter() const { return TickCounter; }
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UPROPERTY()
    TMap<AActor*, FGameStats> TickingGameplays;
    
    UPROPERTY(EditDefaultsOnly)
    uint32 TickCounter;
};
