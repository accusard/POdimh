// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "POdimhSaveGame.h"



void UPOdimhSaveGame::AddTile(int Type)
{
    SavedGrid.TileTypes.Add(Type);
}

const int32 FBoardSaveData::GetNumberOfTiles() const
{
    return TileTypes.Num();
}

UPOdimhSaveGame::UPOdimhSaveGame()
{
    SaveSlotName = DEFAULT_SAVE_SLOT;
    UserIndex = 0;
    
    DEFAULT = DEFAULT_SAVE_SLOT;
    RESET = RESET_GAME_SLOT;
    CONTINUE = CONTINUE_GAME_SLOT;
    PREVIOUS = LAST_SUCCESSFUL_SLOT;
}




