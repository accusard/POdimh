// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "GridEvent.h"
#include "ProjectOdimh.h"
#include "Engine/World.h"
#include "Entities/Game/Grid.h"
#include "Sound/SoundCue.h"





void UGridEvent::SetState(const uint8 New, const uint8 Last)
{
    NewState = New;
    LastState = Last;
    
}


void UGridEvent::OnEventEnd()
{
    Cast<AGrid>(GetOuter())->OnEventEnd();
}
