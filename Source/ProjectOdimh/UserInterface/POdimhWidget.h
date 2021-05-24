// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "POdimhWidget.generated.h"



/**
 * 
 */
UCLASS()
class PROJECTODIMH_API UPOdimhWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UPOdimhWidget(const FObjectInitializer& ObjectInitializer);
    
    virtual void NativeConstruct() override;
    
    UFUNCTION(BlueprintCallable)
    const FText& LoadTooltipTextFromTable(UDataTable* Table, const FName& RowName);
};
