// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UserInterfaceBase.generated.h"

/**
 * TODO: delete class, transferred to AUserTouchInterface
 */
UCLASS()
class PROJECTODIMH_API AUserInterfaceBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUserInterfaceBase();

    // Called every frame
    virtual void Tick(float DeltaTime) override;
    
    // override the property change function to call SetCollisionSize
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
    
    /** The collision size updates both the mesh and arrow components so that they appear at
     the end of the collision box */
    void SetCollisionSize(const FVector& Size);
    
    UFUNCTION()
    void UICommandEnter(ETouchIndex::Type Index, UPrimitiveComponent* TouchedComp);
    UFUNCTION()
    void UICommandLeave(ETouchIndex::Type Index, UPrimitiveComponent* TouchedComp);
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere)
    class UBoxComponent* UICollision;
    UPROPERTY(VisibleAnywhere)
    class UArrowComponent* Arrow;

private:
    /** The size of the collision box will update the location of both the Mesh and Arrow components */
    UPROPERTY(EditAnywhere, Category="Collision")
    FVector CollisionSize;
	
};
