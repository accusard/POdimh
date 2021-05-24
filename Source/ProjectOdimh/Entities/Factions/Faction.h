// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Faction.generated.h"

class UPledge;

/**
 * 
 */
UCLASS()
class PROJECTODIMH_API UFaction : public UObject
{
	GENERATED_BODY()
	
public:
    const int32 GetTotalNumberOfPledges() const;
    
    void AddPledge(UPledge* Pledge);
    
private:
    TArray<UPledge*> TotalPledges;
};
