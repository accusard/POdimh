// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DebuggerInfo.generated.h"

/**
 * Deprecate class. Use PlayerController->ClientMessage() instead
 */
UCLASS()
class PROJECTODIMH_API ADebuggerInfo : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADebuggerInfo();
    
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    
    void PrintToScreen(const FString String);
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere)
    int32 DoNotOverwrite;
    
    UPROPERTY(EditAnywhere)
    float DisplaySeconds;
    
    UPROPERTY(EditAnywhere)
    FString Message;
    
    UPROPERTY(EditAnywhere)
    FColor TextColor;
    
    UPROPERTY(EditAnywhere)
    bool bPrintAboveOld;
    
    UPROPERTY(EditAnywhere)
    FVector2D Scale;
	
};
