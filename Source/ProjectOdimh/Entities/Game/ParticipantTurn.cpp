// Copyright 2017-2019 Vanny Sou. All Rights Reserved.

#include "ParticipantTurn.h"
#include "POdimhGameInstance.h"
#include "POdimhGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Entities/Game/Match3GameMode.h"
#include "Entities/Controllers/Player/GridPlayerController.h"
#include "Components/ActionTurnBasedComponent.h"
#include "Events/GameEvent.h"


// Sets default values
AParticipantTurn::AParticipantTurn()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;
    
    
    
}

void AParticipantTurn::Init(const FString& Name)
{
    AController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), (int32)EPlayer::One);
    
    Init(Name, Controller);
}

void AParticipantTurn::Init(const FString& Name, AController* SetController)
{
    DisplayName = Name;
    GridController = SetController;
    
}

// Called when the game starts or when spawned
void AParticipantTurn::BeginPlay()
{
	Super::BeginPlay();
    
    
}

AController* AParticipantTurn::GetGridController() const
{
    return GridController;
}

const FString& AParticipantTurn::GetDisplayName() const
{
    return DisplayName;
}
