// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Entities/Game/Tile.h"
#include "POdimhSaveGame.generated.h"

const FString DEFAULT_SAVE_SLOT = "DefaultSlotName";
const FString RESET_GAME_SLOT = "ResetLevel";
const FString CONTINUE_GAME_SLOT = "ContinueGame";
const FString LAST_SUCCESSFUL_SLOT = "LastSuccessfulSlot";

USTRUCT()
struct FBaseSaveData
{
    GENERATED_USTRUCT_BODY()
    
public:
    
};

/**
 * The struct that contain the save data of the combat board
 */
USTRUCT(BlueprintType)
struct FBoardSaveData : public FBaseSaveData
{
    GENERATED_USTRUCT_BODY()
    
public:
    FBoardSaveData() {}
        
    /** Get the total tiles that data contained */
    const int32 GetNumberOfTiles() const;
    
    /** Data to hold tile types */
    UPROPERTY(BlueprintReadOnly)
    TArray<int> TileTypes;
    
};

USTRUCT(BlueprintType)
struct FCustomIntData
{
    GENERATED_USTRUCT_BODY()
public:
    FCustomIntData() : FCustomIntData("", 0) {}
    FCustomIntData(const FString& Str, const int Val) : Id(Str), Value(Val) {}
    
    UPROPERTY(BlueprintReadWrite)
    FString Id;
    
    UPROPERTY(BlueprintReadWrite)
    int Value;
};

/**
 * An object that contains the save data of the game
 */
UCLASS()
class PROJECTODIMH_API UPOdimhSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
    UPROPERTY(BlueprintReadOnly)
    FString DEFAULT;
    UPROPERTY(BlueprintReadOnly)
    FString RESET;
    UPROPERTY(BlueprintReadOnly)
    FString CONTINUE;
    UPROPERTY(BlueprintReadOnly)
    FString PREVIOUS;
    
public:
    // default constructor
    UPOdimhSaveGame();
    
    void AddTile(int Type);
    
    /** The name of the save slot */
    UPROPERTY()
    FString SaveSlotName;
    
    /** The user who is doing the save */
    UPROPERTY()
    uint32 UserIndex;
    
    /** The state of the board as well as the current score is kept here */
    UPROPERTY(BlueprintReadOnly)
    FBoardSaveData SavedGrid;
    
    /** Data for the turn queue */
    UPROPERTY()
    TArray<FCustomIntData> ParticipantsRegistry;
    
    UPROPERTY()
    TMap<FString, int32> CustomInt;
    
    UPROPERTY()
    TMap<FString, FIntPoint> CustomIntPoint;

};


