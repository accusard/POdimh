// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "Obstacle.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AObstacle::AObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
    RootComponent = Mesh;
}

void AObstacle::SetupInitialProperties()
{
    
}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

