// Copyright 2017-2021 Vanny Sou. All Rights Reserved.


#include "Data/PointTracker.h"
#include "Events/EventManager.h"
#include "Events/GameEvent.h"
#include "POdimhGameInstance.h"

void APointTracker::NotifyPointsUp(const uint32 Value)
{
    UEventManager* EvtMgr = Cast<UPOdimhGameInstance>(GetGameInstance())->EventManager;
    EvtMgr->CallbackOnCount.Broadcast(this, Value);
}

void APointTracker::NotifyPointsThreshold()
{
    UEventManager* EvtMgr = Cast<UPOdimhGameInstance>(GetGameInstance())->EventManager;
    UGameEvent* ThresholdEvent = EvtMgr->NewEvent<UGameEvent>(this, "Threshold", true);
    EvtMgr->OnActorEvent.Broadcast(this, ThresholdEvent);
}

void APointTracker::Add(const uint32 BaseValue, const uint32 Multiplier)
{
    const uint32 Total = BaseValue * Multiplier;
    Points.Value += Total;
    NotifyPointsUp(Total);
    
    if(Points.Value >= GetThreshold())
        NotifyPointsThreshold();
}

const int32 APointTracker::GetTotalPoints() const
{
    return Points.Value;
}

void APointTracker::SetThreshold(const uint32 Value)
{
    Points.Default = Value;
}

const int32 APointTracker::GetThreshold() const
{
    return Points.Default;
}

const int32 APointTracker::GetDeltaPoints() const
{
    const uint32 Delta = GetThreshold() - GetTotalPoints();
    return Delta;
}
