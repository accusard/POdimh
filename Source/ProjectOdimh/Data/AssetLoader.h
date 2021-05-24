// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Engine/DataTable.h"
#include "AssetLoader.generated.h"

const FString TILE_RELEASE = "SoundCue'/Game/The_Future_Is_Now/cues/2_Confirms/UI_Confirm_68_Cue.UI_Confirm_68_Cue'";
const FString PATH_SOUND_TABLE = "DataTable'/Game/ProjectOdimh/DataTables/SoundDataTable.SoundDataTable'";


class USoundCue;

/**
 * 
 */
USTRUCT()
struct PROJECTODIMH_API FSoundData : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()
    
	FSoundData();

    UPROPERTY()
    TSoftObjectPtr<USoundCue> SoundFile;
};

USTRUCT()
struct PROJECTODIMH_API FTextTableRow : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()
    
    FTextTableRow();
    
    UPROPERTY()
    FText Text;
    
};

UCLASS()
class PROJECTODIMH_API UAssetLoader : public UObject
{
    GENERATED_BODY()
    
public:
    static UDataTable* FindTable(const TCHAR* TableToFind);
    
    static FDataTableRowHandle GetTableHandler(const TCHAR* TableToFind);
    
    static FSoundData* GetSoundFileFromRow(UDataTable* Table, FName RowName, const FString& ContextString);
    
    static FTextTableRow* GetTextFromRow(UDataTable* Table, const FName& RowName, const FString& Context);
    
};



