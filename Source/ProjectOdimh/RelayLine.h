// Copyright 2017-2019 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RelayLine.generated.h"

UCLASS()
class PROJECTODIMH_API ARelayLine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARelayLine();

    // Called every frame
    virtual void Tick(float DeltaTime) override;
    

    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FVector2D> Coordscoocoo;
    

};
