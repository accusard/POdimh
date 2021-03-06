// Copyright 2022 Vanny Sou. All Rights Reserved.

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
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FActorCallBackOnCount, AActor*, Trigger, const int, Num);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCreateFromComponentDelegate, AActor*, Spawner, UActorComponent*, Comp);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FActorEventDelegate, AActor*, Actor, UBaseEvent*, Event);

/**
 * Contains delegates used for multicasting
 */
UCLASS(Blueprintable)
class PROJECTODIMH_API UEventManager : public UObject
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEventManager();
    
    template<class T>
    T* NewEvent(UObject* Outer, FName Identifier, const bool bStartNow)
    {
        T* NewEvent = NewObject<T>(Outer, Identifier);
        if(UBaseEvent* Event = Cast<UBaseEvent>(NewEvent))
        {
            Event->Init();
            if(bStartNow) Event->Start();
            
            AddEvent(Event);
            
            return static_cast<T*>(NewEvent);
        }
        else
        {
            Cast<UObject>(NewEvent)->MarkAsGarbage();
#if !UE_BUILD_SHIPPING
            UE_LOG(LogTemp,Warning,TEXT("- Event Manager is attempting to add to event list but object %s is an invalid event so calling kill immediately."), *NewEvent->GetName());
#endif
            return nullptr;
        }
    }
    
    UFUNCTION(BlueprintCallable, Category="POdimh Events")
    UBaseEvent* NewEvent(TSubclassOf<UBaseEvent> Class, UObject* Outer, FName Description, const bool bStartNow);
    
    /** Iterate through actors in the active UWorld and place in Event Handler list. */
    void InitEventHandlersList(UWorld* World);
    
    void InitEventQueue();
    
    void AddEvent(UBaseEvent* Event);
    
    void EndEvents(const FName EventId);
    
    UFUNCTION(BlueprintCallable, Category="EventManager")
    void ClearEventQueue(const bool bForceClear = false);
    
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
    
    UPROPERTY(BlueprintAssignable, BlueprintCallable)
    FActorEventDelegate OnActorEvent;
    
    UPROPERTY(BlueprintAssignable, BlueprintCallable)
    FActorCallBackOnCount OnTurn;
    
    UPROPERTY(BlueprintAssignable, BlueprintCallable)
    FActorCallBackOnCount OnScoreUp;
    
    FResolveTileCollisions TilesSwapped;
    
private:
    
    /** A list of events that are pending processing */
    UPROPERTY()
    AQueue* EventQueue;
};
