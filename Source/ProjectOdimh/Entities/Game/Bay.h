// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bay.generated.h"

class APowerup;

UCLASS()
class PROJECTODIMH_API ABay : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABay();

    const int GetTileMatchType() const;
    
    /** Spawn a powerup using the given object's transform */
    void SpawnPowerup(UObject* NewPowerup, const FTransform *Transform);
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
    /** The tile type that correspond to this ABay object */
    UPROPERTY(BlueprintReadWrite)
    int TileMatchType;
	
};
