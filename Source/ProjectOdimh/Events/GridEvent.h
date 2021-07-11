// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Events/BaseEvent.h"
#include "GridEvent.generated.h"



class AGrid;

/**
 * 
 */
UCLASS(BlueprintType)
class PROJECTODIMH_API UGridEvent : public UBaseEvent
{
	GENERATED_BODY()
	
    friend class AGrid;
    
public:
    
    
protected:
    UPROPERTY(BlueprintReadOnly, Category="Grid Assets")
    TArray<class ATile*> PtrToTiles;
};
