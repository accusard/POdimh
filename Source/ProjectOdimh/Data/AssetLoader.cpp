// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "AssetLoader.h"
#include "UObject/ConstructorHelpers.h"

FSoundData::FSoundData()
{
    
}

FTextTableRow::FTextTableRow()
{
    
}

UDataTable* UAssetLoader::FindTable(const TCHAR* TableToFind)
{
    static ConstructorHelpers::FObjectFinder<UDataTable> Table(TableToFind);
    
    return Table.Object;
}

FDataTableRowHandle UAssetLoader::GetTableHandler(const TCHAR* TableToFind)
{
    FDataTableRowHandle TableHandler;
    TableHandler.DataTable = FindTable(TableToFind);
    
    return TableHandler;
}

FSoundData* UAssetLoader::GetSoundFileFromRow(UDataTable* Table, FName RowName, const FString& ContextString)
{
    FSoundData* MyRow = nullptr;
    
    return MyRow = Table->FindRow<FSoundData>(RowName, ContextString);
}

FTextTableRow* UAssetLoader::GetTextFromRow(UDataTable* Table, const FName& RowName, const FString& Context)
{
    FTextTableRow* Row = nullptr;
    
    return Row = Table->FindRow<FTextTableRow>(RowName, Context);
}
