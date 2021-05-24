// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PathNode.generated.h"

class AObstacle;

/**
 * APathNode object contain an obstacle and links to other path nodes
 */
UCLASS()
class PROJECTODIMH_API APathNode : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APathNode();

    /** Set the obstacle for this path node */
    void SetObstacle(AObstacle* Set);
    
    /** Get the obstacle currently in this path node */
    const AObstacle* GetObstacle() const;
    
    /** Sets the obstacle object to NULL */
    void ClearObstacle();
    
    /** A reference to the previous node */
    APathNode* PreviousNode;
    
    /** A reference to the next node */
    APathNode* NextNode;
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
    /** The obstacle that is currently in this path node */
    AObstacle* Obstacle;
	
};
