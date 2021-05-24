// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CombatBoard.generated.h"


UCLASS()
class PROJECTODIMH_API ACombatBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACombatBoard();

    // Called every frame
    virtual void Tick(float DeltaTime) override;
    
    void Initialize(AActor* NewPathways, const FVector& NewLocation, const int NumOfInitialBranches = 3);
    
    /** Retrieve all the locations pertaining to the player */
    const TArray<FVector>& GetPlayerBayLocation();
    
    /** Retrieve all the locations pertaining to the enemy */
    const TArray<FVector>& GetEnemyBayLocation();
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    //~ Setters for blueprint variables
	UFUNCTION(BlueprintImplementableEvent)
    void SetPlayerBayFromBlueprint();
	
    UFUNCTION(BlueprintImplementableEvent)
    void SetEnemyBayFromBlueprint();
    
    //~ Data for blueprint variables
    UPROPERTY(BlueprintReadWrite)
    TArray<FVector> PlayerBayLocation_BP_Var;
    
    UPROPERTY(BlueprintReadWrite)
    TArray<FVector> EnemyBayLocation_BP_Var;
    
private:
    AActor* Pathways;
    
};
