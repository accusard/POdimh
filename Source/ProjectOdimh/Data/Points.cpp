// Copyright 2022 Vanny Sou. All Rights Reserved.


#include "Data/Points.h"
#include "Events/EventManager.h"
#include "Events/GameEvent.h"
#include "POdimhGameInstance.h"

void APoints::NotifyPointsUp(const uint32 Value)
{
    UEventManager* EvtMgr = Cast<UPOdimhGameInstance>(GetGameInstance())->EventManager;
    EvtMgr->OnScoreUp.Broadcast(this, Value);
    UE_LOG(LogTemp,Warning,TEXT("PointsUp"));
}

void APoints::NotifyPointsThreshold()
{
    UEventManager* EvtMgr = Cast<UPOdimhGameInstance>(GetGameInstance())->EventManager;
    UGameEvent* GameEvt = EvtMgr->NewEvent<UGameEvent>(this, F_THRESHOLD_EVENT, true);
    EvtMgr->OnActorEvent.Broadcast(this, GameEvt);
    UE_LOG(LogTemp,Warning,TEXT("ThresholdUp"));
}

void APoints::Set(const uint32 Value)
{
    Points.Value = Value;
}

void APoints::Add(const int32 Val, const bool bNotePointsUp)
{
    Points.Value += Val;
    if(bNotePointsUp)
    {
        NotifyPointsUp(Val);
    
        if(Points.Value >= GetThreshold())
            NotifyPointsThreshold();
    }
}

const int32 APoints::GetTotalPoints() const
{
    return Points.Value;
}

void APoints::SetThreshold(const uint32 Value)
{
    Points.Default = Value;
}

const int32 APoints::GetThreshold() const
{
    return Points.Default;
}

const int32 APoints::GetDeltaPoints() const
{
    const uint32 Delta = GetThreshold() - GetTotalPoints();
    return Delta;
}


