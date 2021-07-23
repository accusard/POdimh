// Copyright 2017-2019 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/GameTypes.h"
#include "ClassInterface/DataSaveInterface.h"
#include "RelayLine.generated.h"

UCLASS()
class PROJECTODIMH_API ARelayLine : public AActor, public IDataSaveInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARelayLine();

    virtual void NotifySave(USaveGame* Data) override;
    virtual const bool NotifyLoad(USaveGame* Data) override;
    
    UFUNCTION(BlueprintImplementableEvent)
    void OnSaveFromBlueprint(USaveGame* Data) const;
    UFUNCTION(BlueprintImplementableEvent)
    const bool OnLoadFromBlueprint(USaveGame* Data) const;
    
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    
    UFUNCTION(BlueprintImplementableEvent)
    void InitOnFinished(AActor* Actor, class UBaseEvent* Evt);
    
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
