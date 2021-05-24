// Copyright 2017-2019 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ParticipantTurn.generated.h"

class UGameEvent;

/**
 * Contain the GridController and a DisplayName for the current turn
 */
UCLASS()
class PROJECTODIMH_API AParticipantTurn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AParticipantTurn();
    
    void Init(const FString& Name);
    void Init(const FString& Name, AController* SetGridController);
    
    UFUNCTION(BlueprintCallable, Category="")
    AController* GetGridController() const;
    
    UFUNCTION(BlueprintPure, Category="Participant Turn")
    const FString& GetDisplayName() const;
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
    UPROPERTY(EditAnywhere, Category="Participant Turn")
    FString DisplayName;
    
    UPROPERTY(EditAnywhere, Category="Participant Turn")
    TSubclassOf<AController> ControllerBlueprint;

private:
    AController* GridController;
};
