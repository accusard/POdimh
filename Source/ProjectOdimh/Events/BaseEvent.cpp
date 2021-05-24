// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "Events/BaseEvent.h"
#include "POdimhGameInstance.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"


UBaseEvent::UBaseEvent()
{
    bPendingFinish = true;
    bStarted = false;
    UE_LOG(LogTemp,Warning,TEXT("Creating Event %s"), *GetName());
}

UBaseEvent::~UBaseEvent()
{
    UE_LOG(LogTemp,Warning,TEXT("Destroying Event"));
}

void UBaseEvent::Init()
{
    check(GlobalEventManager = Cast<UPOdimhGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->EventManager);
    check(GameInstance = Cast<UPOdimhGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())));
    check(GameMode = UGameplayStatics::GetGameMode(GetWorld()));
}

void UBaseEvent::Start()
{
    bStarted = true;
    OnEventStart();
}

const bool UBaseEvent::IsPendingFinish() const
{
    return bPendingFinish;
}

const bool UBaseEvent::HasStarted() const
{
    return bStarted;
}

void UBaseEvent::End()
{

    if(bPendingFinish)
    {
        bPendingFinish = false;
        OnEventEnd();
    }
}

void UBaseEvent::ResetEvent()
{
    bPendingFinish = true;
    bStarted = false;
}

UObject* UBaseEvent::GetOwner() const
{
    return GetOuter();
}



