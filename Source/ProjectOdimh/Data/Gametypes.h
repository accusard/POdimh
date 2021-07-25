// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "Gametypes.generated.h"

// constants
const uint32 DEFAULT_MOVE_COST = 1; // the default number of grid moves that a game piece can make per turn
const uint32 MAXIMUM_VALUE_1000 = 1000;

const FName SWAP_POSITIONS = TEXT("Swap Tile Positions");

/** An enum for player ID */
UENUM(BlueprintType)
enum class EPlayer : uint8
{
    One = 0,
    Two
};

// TODO: promote to a TMap?
UENUM()
enum class EMechModule : uint16
{
    Weapon = 0,
    Defense,
    Navigation,
    Max_Type
};


UENUM(BlueprintType)
enum class EDirection : uint8
{
    Up = 0,
    Down = 1,
    Left = 2,
    Right = 3,
    MaxDir
};

USTRUCT()
struct FMatch3GameAction
{
    GENERATED_USTRUCT_BODY()
    
public:
    FName Identifier;
    uint32 Num;
    class AMatch3GameMode* GameMode;
};

USTRUCT(BlueprintType)
struct FIntPointLine
{
    GENERATED_USTRUCT_BODY()
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FIntPoint Start{2,0};
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FIntPoint End{2,5};
};
