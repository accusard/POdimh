// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Controller.h"
#include "GameTypes.h"
#include "ClassInterface/PickHandlerInterface.h"
#include "GridController.generated.h"

const int32 DEFAULT_TILE_SPEED = 25;
class USoundCue;

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class PROJECTODIMH_API AGridController : public AController, public IPickHandlerInterface
{
	GENERATED_BODY()
	
public:
    AGridController();
    
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    
    virtual void BeginPlay() override;
    
    UFUNCTION(BlueprintPure)
    virtual class UActorPickHandlerComponent* GetPickHandler() override;
    
    UFUNCTION(BlueprintImplementableEvent)
    void OnBeginGridCheck(APawn* Grid);
    
    UFUNCTION(BlueprintImplementableEvent)
    void OnHandlePick(AActor* PickedTile);
    
    UFUNCTION(BlueprintCallable)
    EDirection GetRandomDirection();
    
    UFUNCTION(BlueprintCallable)
    ATile* PickRandomTile(AGrid* Grid);
    
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    class UActorPickHandlerComponent* TileHandlerComponent;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    class UActionTurnBasedComponent* ActionComp;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TileSpeed;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector2D CursorVelocity;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    USoundCue* PickCue;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    USoundCue* ReleaseCue;
    
};
