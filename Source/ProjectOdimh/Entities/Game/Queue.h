// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "Entities/Game/ParticipantTurn.h"
#include "Queue.generated.h"



/**
 * A list of entities that can be cycled through and loops in a ringed fashion
 */
UCLASS(Blueprintable)
class PROJECTODIMH_API AQueue : public AInfo
{
	GENERATED_BODY()
	
public:
    // constructor
    AQueue();
    
    /** Add an entity to the back of the list */
    void AddToList(UObject* ObjectToAdd);
    
    void EmptyList();
    
    /** Cycle to the next entity on the list. Will loop back to the first element after the last */
    UFUNCTION(BlueprintCallable, Category="Cycling")
    UObject* CycleNext();
    
    /** Returns the total in the queue list */
    const int32 GetNumObjects() const;
    
    UFUNCTION(BlueprintCallable, Category="Index")
    UObject* GetIndex(const int32 index) const;
    
    void SetCurrentIndex(const int32 index);
    const int32 GetCurrentIndex() const;
    
protected:
    virtual void BeginPlay() override;
    
    /** A list of entities in queue */
    UPROPERTY(EditAnywhere, Category="Edit Queue List")
    TArray<UObject*> List;
    
    /** The current position of the queue when cycling */
    UPROPERTY(BlueprintReadOnly, Category="Index")
    int32 Index;
};

