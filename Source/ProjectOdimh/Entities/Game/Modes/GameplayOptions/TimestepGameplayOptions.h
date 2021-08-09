// Copyright 2017-2021 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ClassInterface/GameplayOptionsInterface.h"
#include "ClassInterface/DataSaveInterface.h"
#include "Data/FGameStats.h"
#include "TimestepGameplayOptions.generated.h"

UCLASS()
class PROJECTODIMH_API ATimestepGameplayOptions : public AActor, public IDataSaveInterface, public IGameplayOptionsInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimestepGameplayOptions();

    virtual void Save(USaveGame* Data) override;
    virtual const bool Load(USaveGame* Data) override;
    
    const int GetOnTickFrom(AActor* Actor);
    
    void AddActorToTick(AActor* Actor, const FGameStats& Tick);
    
    UFUNCTION(BlueprintCallable)
    void ResetActorsTickCounter(TArray<AActor*> ActorArray);
    
    UFUNCTION(BlueprintCallable)
    void SetActorToTickOn(AActor* SetActor, const int TickOn);
    
    UFUNCTION(BlueprintCallable)
    void ResetAllActorsTickDefault();
    
    UFUNCTION()
    void TickStepTimer(AActor* Actor, const int OnTick);
    
    UFUNCTION(BlueprintPure)
    const int GetTickOnTurn(AActor* CheckActor, const int CurrentTurn);
    
    const bool ShouldTick(AActor* CheckActor, const int OnTick);
    const TArray<AActor*> ShouldTick(const int OnTick);
    
    const uint32 GetDefaultStepsBeforeTick() const { return DefaultTick; }
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UPROPERTY()
    TMap<AActor*, FGameStats> TickingActors;
    
    UPROPERTY(EditDefaultsOnly)
    uint32 DefaultTick;
};
