// Copyright 2017-2021 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ClassInterface/GameplayOptionsInterface.h"
#include "Data/FGameStats.h"
#include "Gameplay.generated.h"

UCLASS()
class PROJECTODIMH_API AGameplay : public AActor, public IGameplayOptionsInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameplay();
    
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void Init(AActor* Actor, UBaseEvent* Evt);
    
    const uint32 GetNumOfTicksBeforeRun() const { return NumOfTicksBeforeRun.Value; }
    
protected:
    UPROPERTY(EditDefaultsOnly)
    FGameStats NumOfTicksBeforeRun;



    
};
