// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "SelectButton.h"
#include "ProjectOdimh.h"
#include "Sound/SoundCue.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/AudioComponent.h"
#include "Data/AssetLoader.h"
#include "Events/PlayerInputEvent.h"




USelectButton::USelectButton()
{
    static ConstructorHelpers::FObjectFinder<USoundCue> SoundFile(*TILE_RELEASE);

    ReleaseSoundCue = SoundFile.Object;
}

void USelectButton::BroadcastEvent()
{
    if(UPOdimhGameInstance* Instance = Cast<UPOdimhGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
    {
        Instance->EventManager->OnInteractWidget.Broadcast();
    }
}
