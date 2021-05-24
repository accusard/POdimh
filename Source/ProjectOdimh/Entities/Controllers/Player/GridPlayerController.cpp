// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "GridPlayerController.h"
#include "GameTypes.h"
#include "Sound/SoundCue.h"
#include "UObject/ConstructorHelpers.h"
#include "Entities/Game/Grid.h"
#include "Components/ActorPickHandlerComponent.h"
#include "Components/ActionTurnBasedComponent.h"
#include "Events/PlayerInputEvent.h"
#include "Events/TurnEvent.h"
#include "POdimhGameInstance.h"


AGridPlayerController::AGridPlayerController()
{
    TileHandlerComponent = CreateDefaultSubobject<UActorPickHandlerComponent>("Tile Handler");
    ActionComp = CreateDefaultSubobject<UActionTurnBasedComponent>("Turn-Based Action Handler");
    
    static ConstructorHelpers::FObjectFinder<USoundCue> DefaultGrabSoundCue(TEXT("SoundCue'/Game/The_Future_Is_Now/cues/1_Neutral/UI_Neutral_173_Cue.UI_Neutral_173_Cue'"));
    
    static ConstructorHelpers::FObjectFinder<USoundCue> DefaultReleaseSoundCue(TEXT("SoundCue'/Game/The_Future_Is_Now/cues/1_Neutral/UI_Neutral_205_Cue.UI_Neutral_205_Cue'"));
    
    if(DefaultGrabSoundCue.Object)
        PickCue = DefaultGrabSoundCue.Object;
    
    if(DefaultReleaseSoundCue.Object)
        ReleaseCue = DefaultReleaseSoundCue.Object;
    bAutoManageActiveCameraTarget = false;
}

void AGridPlayerController::BeginPlay()
{
    Super::BeginPlay();
    Cast<UPOdimhGameInstance>(GetGameInstance())->EventManager->OnActorPicked.AddDynamic(this, &AGridPlayerController::HandlePick);
}

UActorPickHandlerComponent* AGridPlayerController::GetPickHandler()
{
    return TileHandlerComponent;
}

void AGridPlayerController::HandlePick(AActor* PickedTile)
{
    GetPickHandler()->SetPlayerControlled();
}

void AGridPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    
    InputComponent->BindTouch(IE_Pressed, this, &AGridPlayerController::BeginTouch);
    InputComponent->BindTouch(IE_Released, this, &AGridPlayerController::EndTouch);
    
}

void AGridPlayerController::BeginTouch(ETouchIndex::Type FingerIndex, FVector Location)
{
    if(GridPtr->IsPickState() && TileHandlerComponent)
    {
        FHitResult Hit = FHitResult();
        NewInput("Player Input Event", false);
        
        if(GetHitResultUnderFinger(FingerIndex, ECollisionChannel::ECC_WorldDynamic, false, Hit))
        {
            if(GrabActor(this, TileHandlerComponent, Hit))
                InputEvent->Start();
        }
    }
}

void AGridPlayerController::EndTouch(ETouchIndex::Type FingerIndex, FVector Location)
{
    if(InputEvent)
        InputEvent->End();
}

AActor* AGridPlayerController::GetLastTouched()
{
    AActor* LastTouched = Cast<IPickHandlerInterface>(this)->GetLastGrab(TileHandlerComponent);
    return LastTouched;
}

void AGridPlayerController::NewInput(const FName& Name, const bool bStartNow)
{
    if(InputEvent && !InputEvent->IsPendingKill())
    {
        InputEvent->End();
        InputEvent->MarkPendingKill();
    }
    InputEvent = Cast<UPOdimhGameInstance>(GetGameInstance())->EventManager->NewEvent<UPlayerInputEvent>(this, Name, bStartNow);
}

void AGridPlayerController::ForceRelease()
{
    Execute_OnReleaseActor(this, TileHandlerComponent);
}
