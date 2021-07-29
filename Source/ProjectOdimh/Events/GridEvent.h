// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Events/BaseEvent.h"
#include "GridEvent.generated.h"



class ATile;

/**
 * 
 */
UCLASS(BlueprintType)
class PROJECTODIMH_API UGridEvent : public UBaseEvent
{
	GENERATED_BODY()
	
    friend class AGrid;
    
public:
    virtual void OnEventEnd() override;
    
    UFUNCTION(BlueprintCallable, Category="Grid States")
    void SetState(const uint8 New, const uint8 Last);
    
    
protected:
    UPROPERTY(BlueprintReadWrite, Category="Tile Data")
    TArray<ATile*> PtrToCustomTiles;
    
    UPROPERTY(BlueprintReadWrite, Category="Tile Data")
    TArray<ATile*> TilesToBurst;
    
    UPROPERTY(BlueprintReadOnly, Category="Grid States")
    uint8 NewState;
    
    UPROPERTY(BlueprintReadOnly, Category="Grid States")
    uint8 LastState;
};
