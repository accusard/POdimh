// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "ModuleAssembler.generated.h"

class AMechClass;
class AModuleActor;

/**
 * An abstract class that assembles a class for a mech
 */
UCLASS(abstract)
class PROJECTODIMH_API AModuleAssembler : public AInfo
{
	GENERATED_BODY()
	
public:
    /** Create a mech from the specified module */
    virtual AMechClass* Assemble(AModuleActor* Module);
	
private:
    
};
