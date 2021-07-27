// Copyright 2017-2019 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/GameTypes.h"
#include "Data/POdimhSaveGame.h"
#include "ClassInterface/DataSaveInterface.h"
#include "ClassInterface/GameplayOptionsInterface.h"
#include "RelayLine.generated.h"

class UBaseEvent;

UCLASS()
class PROJECTODIMH_API ARelayLine : public AActor, public IDataSaveInterface, public IGameplayOptionsInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARelayLine();

    virtual void NotifySave(USaveGame* Data) override;
    virtual const bool NotifyLoad(USaveGame* Data) override;
    
    virtual void Run() override;
    
    UFUNCTION(BlueprintImplementableEvent)
    const TArray<FCustomIntData> OnSaveFromBlueprint() const;
    UFUNCTION(BlueprintImplementableEvent)
    const bool OnLoadFromBlueprint(const TArray<FCustomIntData>& Data);
    
    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
    void InitOnFinished(AActor* Actor, UBaseEvent* Evt);
    
    UFUNCTION(BlueprintPure)
    TArray<ATile*> GetUnusedTiles(class AGrid* Grid);
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    FIntPointLine LineCoords;
    
    UPROPERTY(BlueprintReadWrite)
    TArray<FIntPoint> ReservedGridCoords;
    

};
