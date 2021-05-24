// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "MomentumPlayState.h"




AMomentumPlayState::AMomentumPlayState()
{
    TileMatchComboCount = FGameStats();
}

const uint32 AMomentumPlayState::GetCurrentTileComboCount() const
{
    return TileMatchComboCount.Remaining;
}

void AMomentumPlayState::SetMaximumTileComboCount(const uint32 NewCount)
{
    TileMatchComboCount.Maximum = NewCount;
}

void AMomentumPlayState::IncrementTileComboCount()
{
    TileMatchComboCount.Remaining++;
}
