// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PathNodeMovement.generated.h"

class APathNode;
class APathways;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTODIMH_API UPathNodeMovement : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPathNodeMovement();

    /** Checks the given path node for obstacles */
    const bool TryMoveTo(APathways* Path, APathNode* Node) const;
    
    
protected:
	// Called when the game starts
	virtual void BeginPlay() override;


		
	
};
