// Copyright 2017-2019 Vanny Sou. All Rights Reserved.


#include "RandomGridController.h"
#include "Entities/Game/Grid.h"
#include "Entities/Game/Tile.h"


EDirection ARandomGridController::GetRandomDirection()
{
    const int32 Max = (int32)EDirection::MaxDir - 1;
    
    EDirection Direction = static_cast<EDirection>(FMath::RandRange(0, Max));
    
    return Direction;
    
}




