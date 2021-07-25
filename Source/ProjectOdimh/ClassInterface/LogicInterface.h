// Copyright 2017-2021 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LogicInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class ULogicInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTODIMH_API ILogicInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    virtual void OnStart();
    virtual void Process();
};
