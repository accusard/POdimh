// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThoughtBubble.generated.h"

UCLASS()
class PROJECTODIMH_API AThoughtBubble : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AThoughtBubble();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
