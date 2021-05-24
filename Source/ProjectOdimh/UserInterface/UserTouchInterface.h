// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UserTouchInterface.generated.h"

UCLASS()
class PROJECTODIMH_API AUserTouchInterface : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUserTouchInterface();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	
    /** Determine when a UI command enters the trigger box */
    UFUNCTION()
    void UICommandEnter(ETouchIndex::Type Index, UPrimitiveComponent* TouchedComp);
    
    /** Determine when a UI command leaves the trigger box */
    UFUNCTION()
    void UICommandLeave(ETouchIndex::Type Index, UPrimitiveComponent* TouchedComp);
    
protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
    /** The box that determines when a user's touch enters or leaves*/
    UPROPERTY(VisibleAnywhere)
    class UBoxComponent* TriggerBox;
    
private:
    UPROPERTY(EditAnywhere, Category="Touch")
    FVector CollisionSize;
};
