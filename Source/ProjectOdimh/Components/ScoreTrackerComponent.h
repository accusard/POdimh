// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ScoreTrackerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTODIMH_API UScoreTrackerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UScoreTrackerComponent();

    /** Add the given value to the total score */
    void Add(const int Value);
    
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
    uint32 TotalScore;
	
};
