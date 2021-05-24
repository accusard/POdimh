// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "POdimhWidget.h"
#include "UserInterface/SelectButton.h"
#include "Components/Button.h"
#include "Data/AssetLoader.h"
#include "Runtime/UMG/Public/Blueprint/WidgetTree.h"



UPOdimhWidget::UPOdimhWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UPOdimhWidget::NativeConstruct()
{
    Super::NativeConstruct();

    TArray<UWidget*> WidgetList;
    WidgetTree->GetAllWidgets(WidgetList);
    
    for(UWidget* Widget : WidgetList)
    {
        if(USelectButton* Button = Cast<USelectButton>(Widget))
            Button->OnReleased.AddUniqueDynamic(Button, &USelectButton::BroadcastEvent);
    }
}

const FText& UPOdimhWidget::LoadTooltipTextFromTable(UDataTable* Table, const FName& RowName)
{
    return UAssetLoader::GetTextFromRow(Table, RowName, "Tooltip")->Text;
    
}

