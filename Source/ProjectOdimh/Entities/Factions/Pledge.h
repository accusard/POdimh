// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Pledge.generated.h"

/**
 * A pledge hold a unique ID of a user in addition to its name
 */
UCLASS()
class PROJECTODIMH_API UPledge : public UObject
{
	GENERATED_BODY()
	
public:
    const int64 GetUniqueID() const;
	
private:
    int64 UniqueID;
};
