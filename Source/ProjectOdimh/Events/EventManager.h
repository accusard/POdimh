// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Events/BaseEvent.h"
#include "Events/GridEvent.h"
#include "EventManager.generated.h"

class UEventListener;
class UGridEvent;
class AQueue;
class ATile;

DECLARE_DELEGATE_RetVal_TwoParams(const bool, FResolveTileCollisions, ATile*, ATile*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGlobalWidgetDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPickHandler, AActor*, HandleActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCreateFromComponentDelegate, AActor*, Spawner, UActorComponent*, Comp);

/**
 * Contains delegates used for multicasting
 */
UCLASS()
class PROJECTODIMH_API UEventManager : public UObject
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEventManager();
    
    template<class T>
    T* NewEvent(UObject* Outer, FName Name, const bool bStartNow)
    {
        T* NewEvent = NewObject<T>(Outer, Name);
        if(UBaseEvent* Event = Cast<UBaseEvent>(NewEvent))
        {
            Event->Init();
            if(bStartNow) Event->Start();
            
            AddEvent(Event);
            
            return static_cast<T*>(NewEvent);
        }
        else
        {
            Cast<UObject>(NewEvent)->MarkPendingKill();
#if !UE_BUILD_SHIPPING
            UE_LOG(LogTemp,Warning,TEXT("- Event Manager is attempting to add to event list but object %s is an invalid event so calling kill immediately."), *NewEvent->GetName());
#endif
            return nullptr;
        }
    }
    
    /** Iterate through actors in the active UWorld and place in Event Handler list. */
    void InitEventHandlersList(UWorld* World);
    
    void InitEventQueue();
    
    void AddEvent(UBaseEvent* Event);
    
    UFUNCTION(BlueprintCallable)
    void ClearEventQueue();
    
    const int32 GetNumEventsInQueue() const;
    
    const bool HasA(TSubclassOf<UBaseEvent> EventClass);
    
    TArray<class UBaseEvent*> FindAll(TSubclassOf<UBaseEvent> EventClass);
    
    UPROPERTY(BlueprintAssignable)
    FCreateFromComponentDelegate OnSpawnFromComponent;
    
    UPROPERTY(BlueprintAssignable)
    FGlobalWidgetDelegate OnInteractWidget;
    
    UPROPERTY()
    FPickHandler OnActorReleased;
    UPROPERTY()
    FPickHandler OnActorPicked;
    
    FResolveTileCollisions TilesSwapped;
    
private:
    
    /** A list of events that are pending processing */
    UPROPERTY()
    AQueue* EventQueue;
};
