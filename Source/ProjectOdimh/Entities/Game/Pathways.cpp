// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "Pathways.h"
#include "Entities/Game/PathNode.h"
#include "Engine/World.h"

// Sets default values
APathways::APathways()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    CurrentPath = nullptr;
}

void APathways::Setup(const int InitialBranches)
{
    // set current path
    AActor* Path = GetWorld()->SpawnActor(APathNode::StaticClass());
    
    SetCurrentPath(Path);
    
    // branch paths
    for(int i = 0; i < InitialBranches; i++)
    {
        AActor* PathNode = GetWorld()->SpawnActor(APathNode::StaticClass());
        Branches.Add(PathNode);
    }

}

void APathways::SetCurrentPath(AActor* SetPathNode)
{
    CurrentPath = SetPathNode;
}

const int APathways::GetNumberOfBranches() const
{
    return Branches.Num();
}

const bool APathways::Move(AActor* Node)
{
    bool Success = false;
    int32 FoundIndex = -1;
    
    Success = Branches.Find(Node, FoundIndex);
    
    if(Success)
    {
        SetCurrentPath(Branches[FoundIndex]);
    }
    return Success;
}

// Called when the game starts or when spawned
void APathways::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APathways::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

