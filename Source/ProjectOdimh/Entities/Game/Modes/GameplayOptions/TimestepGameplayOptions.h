// Copyright 2017-2021 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ClassInterface/GameplayOptionsInterface.h"
#include "ClassInterface/DataSaveInterface.h"
#include "Utilities/FGameStats.h"
#include "TimestepGameplayOptions.generated.h"

UCLASS()
class PROJECTODIMH_API ATimestepGameplayOptions : public AActor, public IDataSaveInterface, public IGameplayOptionsInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimestepGameplayOptions();

    virtual void NotifySave(USaveGame* Data) override;
    virtual const bool NotifyLoad(USaveGame* Data) override;
    
    const int GetStepTimer(AActor* Actor);
    
    void AddActorToTick(AActor* Actor);
    
    UFUNCTION(BlueprintCallable)
    void ResetActorsTickCounter(TArray<AActor*> ActorArray);
    
    UFUNCTION()
    void TickStepTimer(AActor* Actor, const int OnTick);
    
    const TArray<AActor*> ShouldTick();
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UPROPERTY()
    TMap<AActor*, int> TickingActors;
};
