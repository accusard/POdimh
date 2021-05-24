// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pathways.generated.h"


/**
 * Contain a reference to the current path and multiple branches of path nodes
 */
UCLASS()
class PROJECTODIMH_API APathways : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APathways();

    void Setup(const int InitialBranches);
    
    void SetCurrentPath(AActor* SetPathNode);
    
    const int GetNumberOfBranches() const;
    
    /** Move to the specified node and return true if the PathNode exist on this path way */
    const bool Move(AActor* PathNode);
    
    TArray<AActor*> Branches;
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
    AActor* CurrentPath;
	
};
