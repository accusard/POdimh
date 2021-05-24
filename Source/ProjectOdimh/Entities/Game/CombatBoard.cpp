// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "CombatBoard.h"
#include "Entities/Game/Pathways.h"
#include "Engine/World.h"

// Sets default values
ACombatBoard::ACombatBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called every frame
void ACombatBoard::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
}

// Called when the game starts or when spawned
void ACombatBoard::BeginPlay()
{
	Super::BeginPlay();
	
    GetPlayerBayLocation();
    GetEnemyBayLocation();
    
    AActor* SpawnPathways = GetWorld()->SpawnActor(APathways::StaticClass());
    Initialize(SpawnPathways, EnemyBayLocation_BP_Var[0]);
}

void ACombatBoard::Initialize(AActor* NewPathways, const FVector& NewLocation,
                                      const int NumOfInitialBranches /** = 3 */)
{
    Pathways = NewPathways;
    
    NewPathways->SetActorLocation(NewLocation);
    
    Cast<APathways>(NewPathways)->Setup(NumOfInitialBranches);
    
    // TODO: finish intializing CombatBoard
}

const TArray<FVector>& ACombatBoard::GetPlayerBayLocation()
{
    SetPlayerBayFromBlueprint();
    return PlayerBayLocation_BP_Var;
}

const TArray<FVector>& ACombatBoard::GetEnemyBayLocation()
{
    SetEnemyBayFromBlueprint();
    return EnemyBayLocation_BP_Var;
}
