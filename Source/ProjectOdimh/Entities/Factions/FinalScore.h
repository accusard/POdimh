// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FinalScore.generated.h"

class UFaction;

/**
 * 
 */
UCLASS()
class PROJECTODIMH_API UFinalScore : public UObject
{
	GENERATED_BODY()
	
public:
    UFinalScore();
    
    void SetOdimhFaction(UFaction* Faction);
    void SetOrganicFaction(UFaction* Faction);
    
    UFaction* GetOdimhFaction() const;
    UFaction* GetOrganicFaction() const;
    
private:
    UFaction* OdimhFaction;
    
    UFaction* OrganicFaction;
	
};
