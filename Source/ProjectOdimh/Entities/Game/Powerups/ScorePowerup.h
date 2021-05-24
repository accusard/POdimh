// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Entities/Game/Powerups/Powerup.h"
#include "ScorePowerup.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTODIMH_API AScorePowerup : public APowerup
{
	GENERATED_BODY()
	
public:
    void SetScoreValue(const int SetValue);
    
    virtual void Activate(AActor* Target) override;
	
private:
    UPROPERTY(EditAnywhere)
    int ScoreValue = 0;
};
