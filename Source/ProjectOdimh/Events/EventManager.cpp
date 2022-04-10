// Copyright 2022 Vanny Sou. All Rights Reserved.

#include "EventManager.h"
#include "EngineUtils.h"
#include "Engine/World.h"
#include "Events/BaseEvent.h"
#include "Events/GridEvent.h"
#include "Events/GameEvent.h"
#include "Entities/Game/Queue.h"


// Sets default values for this component's properties
UEventManager::UEventManager()
{
    EventQueue = CreateDefaultSubobject<AQueue>("Event Queue");
    InitEventQueue();
}

UBaseEvent* UEventManager::NewEvent(TSubclassOf<UBaseEvent> Class, UObject* Outer, FName Description, const bool bStartNow)
{
    UBaseEvent* Event = NewObject<UBaseEvent>(Outer, Class, Description);
    
    Event->Init();
    if(bStartNow) Event->Start();
        
    AddEvent(Event);
    
    return Event;
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
        Event->MarkAsGarbage();
#if !UE_BUILD_SHIPPING
        UE_LOG(LogTemp,Warning,TEXT("- Couldn't add event %s, so calling End() and kill immediately."), *Event->GetName());
#endif
    }
}

void UEventManager::EndEvents(const FName EventId)
{
    UE_LOG(LogTemp,Warning,TEXT("EndEvents object contain - %i"), EventQueue->GetNumObjects());
    int size = EventQueue->GetNumObjects();
    for(int i = 0; i < size; ++i)
    {
        if(UBaseEvent* EvtPending = Cast<UBaseEvent>(EventQueue->GetIndex(i)))
        {
            if(EvtPending->Is(EventId))
            {
                UE_LOG(LogTemp,Warning,TEXT("Ending Event (%s)"), *EvtPending->GetName());
                EvtPending->End();
            }
        }
    }
}

void UEventManager::ClearEventQueue(const bool bForceClear)
{
    for(int i = 0; i < EventQueue->GetNumObjects(); ++i)
    {
        UObject* Obj = EventQueue->GetIndex(i);
        if(IsValid(Obj))
        {
            if(UBaseEvent* Evt = Cast<UBaseEvent>(Obj))
                if(!bForceClear && Evt->IsPendingFinish())
                    continue;
            Obj->MarkAsGarbage();
        }
        
    }
#if !UE_BUILD_SHIPPING
    UE_LOG(LogTemp,Warning,TEXT("Clearing event queue: %i"), EventQueue->GetNumObjects());
#endif
    EventQueue->EmptyList();
}

