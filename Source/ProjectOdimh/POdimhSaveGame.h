// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Entities/Game/Tile.h"
#include "POdimhSaveGame.generated.h"

const FString DEFAULT_SAVE_SLOT = "DefaultSlotName";
const FString RESET_GAME_SLOT = "ResetLevel";
const FString CONTINUE_GAME_SLOT = "ContinueGame";

USTRUCT()
struct FBaseSaveData
{
    GENERATED_USTRUCT_BODY()
    
public:
    /** When true, the associated data will be reset to its original RESET_GAME_SLOT save by GameInstance->ResetGame(),
     otherwise data will be persistance throughout the entire game */
    uint8 bReset : 1;
};

/**
 * The struct that contain the save data of the mech
 */
USTRUCT()
struct FMechSaveData : public FBaseSaveData
{
    GENERATED_USTRUCT_BODY()
    
public:
    FMechSaveData();
    FVector Position;
};

/**
 * The struct that contain the save data of the combat board
 */
USTRUCT(BlueprintType)
struct FBoardSaveData : public FBaseSaveData
{
    GENERATED_USTRUCT_BODY()
    
public:
    FBoardSaveData()
    {
        GameScore = 0;
    }
    /** Add to the data the type of tile */
    void AddTile(int Type);
    
    /** Get the total tiles that data contained */
    const int32 GetNumberOfTiles() const;
    
    /** Data to hold tile types */
    UPROPERTY(BlueprintReadOnly)
    TArray<int> TileTypes;
    
    UPROPERTY(BlueprintReadOnly)
    TArray<FVector2D> NodeLocations;
    
    /** The data for game score */
    UPROPERTY()
    int32 GameScore;
};

USTRUCT()
struct FParticipantInfo : public FBaseSaveData
{
    GENERATED_USTRUCT_BODY()
    
public:
    FParticipantInfo();
    FParticipantInfo(const FString &Name, const uint32 TurnPosition);
    
    /** The name of the entity being saved */
    UPROPERTY()
    FString Name;
    
    /** The entity's position in the queue to determine when its turn to act */
    UPROPERTY()
    uint32 PositionInQueue;
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
    
public:
    // default constructor
    UPOdimhSaveGame();
    
    /** The name of the save slot */
    UPROPERTY()
    FString SaveSlotName;
    
    /** The user who is doing the save */
    UPROPERTY()
    uint32 UserIndex;
    
    /** The state of the board as well as the current score is kept here */
    UPROPERTY(BlueprintReadOnly)
    FBoardSaveData Board;
    
    /** The list of mechs contained in a given game */
    UPROPERTY()
    TArray<FMechSaveData> MechList;
    
    /** Data for the turn queue */
    UPROPERTY()
    TArray<FParticipantInfo> ParticipantsRegistry;
    
    UPROPERTY()
    uint32 CurrentParticipantIndex;
};


