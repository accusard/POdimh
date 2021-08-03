// Copyright 2017-2021 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ClassInterface/GameplayOptionsInterface.h"
#include "Logic.generated.h"

UCLASS()
class PROJECTODIMH_API ALogic : public AActor, public IGameplayOptionsInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALogic();
    
protected:


private:
    UPROPERTY()
    TArray<AActor*> Logic;
};
