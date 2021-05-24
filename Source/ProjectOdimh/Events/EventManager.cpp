// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "EventManager.h"
#include "EngineUtils.h"
#include "Engine/World.h"
#include "Events/BaseEvent.h"
#include "Events/GridEvent.h"
#include "Events/GameEvent.h"
#include "Components/EventListener.h"
#include "Entities/Game/Queue.h"


// Sets default values for this component's properties
UEventManager::UEventManager()
{
    EventQueue = CreateDefaultSubobject<AQueue>("Event Queue");
    InitEventQueue();
}

const int32 UEventManager::GetNumEventsInQueue() const
{
    return EventQueue->GetNumObjects();
    
}

const bool UEventManager::HasA(TSubclassOf<UBaseEvent> EventClass)
{
    bool HasEvent = false;
    
    for(int i = 0; i < EventQueue->GetNumObjects(); i++)
    {
        if(UObject* EventPtr = EventQueue->GetIndex(i))
        {
            if(EventPtr->IsA(EventClass))
            {
                HasEvent = true;
                break;
            }
        }
    }
    
    return HasEvent;
}

TArray<UBaseEvent*> UEventManager::FindAll(TSubclassOf<UBaseEvent> EventClass)
{
    TArray<UBaseEvent*> Events;
    for(int i = 0; i < EventQueue->GetNumObjects(); i++)
    {
        if(UBaseEvent* EventPtr = Cast<UBaseEvent>(EventQueue->GetIndex(i)))
        {
            if(EventPtr->IsA(EventClass))
                Events.Add(EventPtr);
        }
    }
    return Events;
}

void UEventManager::InitEventQueue()
{
    if(!EventQueue)
        EventQueue = GetWorld()->SpawnActor<AQueue>();
    
}

void UEventManager::AddEvent(UBaseEvent* Event)
{
    if(EventQueue)
        EventQueue->AddToList(Event);
    else
    {
        Event->End();
        Event->MarkPendingKill();
#if !UE_BUILD_SHIPPING
        UE_LOG(LogTemp,Warning,TEXT("- Couldn't add event %s, so calling End() and kill immediately."), *Event->GetName());
#endif
    }
}

void UEventManager::ClearEventQueue()
{
    for(int i = 0; i < EventQueue->GetNumObjects(); ++i)
    {
        UObject* Obj = EventQueue->GetIndex(i);
        if(!Obj->IsPendingKill())
           Obj->MarkPendingKill();
    }
#if !UE_BUILD_SHIPPING
    UE_LOG(LogTemp,Warning,TEXT("Clearing event queue, total: %i"), EventQueue->GetNumObjects());
#endif
    EventQueue->EmptyList();
}

