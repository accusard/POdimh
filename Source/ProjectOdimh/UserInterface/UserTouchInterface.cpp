// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "UserTouchInterface.h"
#include "Components/BoxComponent.h"



// Sets default values
AUserTouchInterface::AUserTouchInterface()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(FName("Trigger Box"));
    TriggerBox->SetCollisionProfileName(TEXT("UI"));
    RootComponent = TriggerBox;
    
    CollisionSize = FVector(60.f, 75.f, 32.f);
}

// Called when the game starts or when spawned
void AUserTouchInterface::BeginPlay()
{
	Super::BeginPlay();
	TriggerBox->OnInputTouchEnter.AddUniqueDynamic(this, &AUserTouchInterface::UICommandEnter);
    TriggerBox->OnInputTouchLeave.AddUniqueDynamic(this, &AUserTouchInterface::UICommandLeave);
}

// Called every frame
void AUserTouchInterface::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUserTouchInterface::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);
    
    TriggerBox->SetBoxExtent(CollisionSize, true);
}

void AUserTouchInterface::UICommandEnter(ETouchIndex::Type Index, UPrimitiveComponent* TouchedComp)
{
    UE_LOG(LogTemp, Warning, TEXT("Command Enters... now do something."));
}

void AUserTouchInterface::UICommandLeave(ETouchIndex::Type Index, UPrimitiveComponent* TouchedComp)
{
    UE_LOG(LogTemp, Warning, TEXT("Command Leaves... now stop doing something."));
}
