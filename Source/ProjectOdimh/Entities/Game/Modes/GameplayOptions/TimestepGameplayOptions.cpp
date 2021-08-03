// Copyright 2017-2021 Vanny Sou. All Rights Reserved.


#include "Entities/Game/Modes/GameplayOptions/TimestepGameplayOptions.h"
#include "POdimhGameInstance.h"



// Sets default values
ATimestepGameplayOptions::ATimestepGameplayOptions()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ATimestepGameplayOptions::NotifySave(USaveGame* Data)
{
    if(UPOdimhSaveGame* POdimhData = Cast<UPOdimhSaveGame>(Data))
    {
        POdimhData->CustomInt.Add(TEXT("TimestepCounter"), Counter);
    }
}

const bool ATimestepGameplayOptions::NotifyLoad(USaveGame* Data)
{
    if(UPOdimhSaveGame* POdimhData = Cast<UPOdimhSaveGame>(Data))
    {
        if(POdimhData->CustomInt.Find(TEXT("TimestepCounter")))
        {
            Counter = POdimhData->CustomInt[TEXT("TimestepCounter")];
            return true;
        }
    }
    
    
    return false;
}

// Called when the game starts or when spawned
void ATimestepGameplayOptions::BeginPlay()
{
	Super::BeginPlay();
    
    Reset();
    
    Cast<UPOdimhGameInstance>(GetGameInstance())->EventManager->OnActorEvent.AddDynamic(this, &ATimestepGameplayOptions::Receive);
}

void ATimestepGameplayOptions::Reset()
{
    Counter = 0;
    TargetStep = 0;
}

void ATimestepGameplayOptions::Receive_Implementation(AActor* ReceiveFrom, UBaseEvent* EvtPtr)
{
    if(Counter >= TargetStep)
    {
        // broadcast
        EvtPtr->Manager->GameplayTrigger.Broadcast(this);
        
        // reset
        Reset();
    }
}
