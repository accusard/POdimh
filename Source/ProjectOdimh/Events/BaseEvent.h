// Copyright 2022 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseEvent.generated.h"

// for event identifiers
static const FName F_THRESHOLD_EVENT(TEXT("Threshold Event"));
static const FName F_INIT_TILE_SPAWN_EVENT(TEXT("Initial Spawn"));
static const FName F_GRID_STATE_CHANGE_EVENT(TEXT("Grid State Change"));
static const FName F_GAME_HAS_STARTED_EVENT(TEXT("Game Has Started"));

class UEventManager;
class UPOdimhGameInstance;



/**
 *
 */
UCLASS(abstract, BlueprintType)
class PROJECTODIMH_API UBaseEvent : public UObject
{
	GENERATED_BODY()
	
public:
    
    UPROPERTY(BlueprintReadOnly, Category="Event Identifier")
    FName THRESHOLD_EVENT;
    
    UPROPERTY(BlueprintReadOnly, Category="Event Identifier")
    FName INIT_TILE_SPAWN_EVENT;
    
    UPROPERTY(BlueprintReadOnly, Category="Event Identifier")
    FName GRID_STATE_CHANGE_EVENT;
    
    UPROPERTY(BlueprintReadOnly, Category="Event Identifier")
    FName GAME_HAS_STARTED_EVENT;
    
public:
    UBaseEvent();
    ~UBaseEvent();
    
    virtual void Init();
    
    /** Identify an event by a static event identifier */
    UFUNCTION(BlueprintPure, Category="POdimh Event")
    const bool Is(const FName EventId) const;
    
    void Start();
    
    virtual void OnEventStart() {}
    virtual void OnEventEnd() {}

    /** Perform any final event processing and let the state of the event know that it has finished */
    void End();
    
    void Reset();
    
    /** Checks if End() have not been called yet */
    UFUNCTION(BlueprintPure, Category="POdimh Event")
    const bool IsPendingFinish() const;
    
    UFUNCTION(BlueprintPure, Category="POdimh Event")
    const bool HasStarted() const;
    
    UPROPERTY(BlueprintReadOnly, Category="POdimh Event")
    UEventManager* Manager;

    UPROPERTY(BlueprintReadOnly, Category="POdimh Event")
    UPOdimhGameInstance* GameInstance;
    
    UPROPERTY(BlueprintReadOnly, Category="POdimh Event")
    AGameModeBase* GameMode;
    
    UObject* GetOwner() const;
    
private:
    uint16 bPendingFinish : 1;
    uint16 bStarted : 1;
};
