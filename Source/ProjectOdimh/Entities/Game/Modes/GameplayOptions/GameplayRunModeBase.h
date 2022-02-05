// Copyright 2022 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ClassInterface/DataSaveInterface.h"
#include "ClassInterface/TurnEventInterface.h"
#include "Data/FGameStats.h"
#include "GameplayRunModeBase.generated.h"

UCLASS()
class PROJECTODIMH_API AGameplayRunModeBase : public AActor, public IDataSaveInterface, public ITurnEventInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameplayRunModeBase();

    // interfaces
    virtual void Save(USaveGame* Data) override;
    virtual const bool Load(USaveGame* Data) override;
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void OnTurnEnd(AActor* EvtCaller, UBaseEvent* Event);
    
    const int GetOnTickFrom(AActor* Gameplay);
    
    UFUNCTION(BlueprintCallable)
    void SetGameplayToTickOn(AActor* SetGameplay, const FGameStats& Tick);
    
    UFUNCTION()
    void StepTick(AActor* Gameplay, const int OnTick);
    
    UFUNCTION(BlueprintPure)
    const int GetTurnNumBeforeRun(AActor* CheckGameplay, const int CurrentTurn);
    
    const bool ShouldTick(AActor* CheckGameplay, const int OnTick);
    const TArray<AActor*> ShouldTick(const int OnTick);
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UPROPERTY()
    TArray<AActor*> TickingGameplays;
    
    UPROPERTY(BlueprintReadOnly)
    FGameStats RunCount = FGameStats(0,1);

};
