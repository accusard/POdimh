// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "SelectButton.generated.h"

class USoundCue;
/**
 * 
 */
UCLASS()
class PROJECTODIMH_API USelectButton : public UButton
{
	GENERATED_BODY()
	
public:
    USelectButton();
    
    UFUNCTION()
    void BroadcastEvent();
    
    UPROPERTY(EditAnywhere)
    USoundCue* ReleaseSoundCue;
	
	
};
