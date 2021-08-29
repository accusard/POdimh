// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseEvent.generated.h"

class UEventManager;
class UPOdimhGameInstance;

/**
 * A UBaseEvent class is a wrapper class that responds to an event that just happend in an encapsulated process.
 */
UCLASS(abstract, BlueprintType)
class PROJECTODIMH_API UBaseEvent : public UObject
{
	GENERATED_BODY()
	
public:
    UBaseEvent();
    ~UBaseEvent();
    
    virtual void Init();
    
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
