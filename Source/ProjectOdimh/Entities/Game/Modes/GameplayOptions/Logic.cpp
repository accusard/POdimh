// Copyright 2017-2021 Vanny Sou. All Rights Reserved.


#include "Entities/Game/Modes/GameplayOptions/Logic.h"
#include "ClassInterface/LogicInterface.h"

// Sets default values
ALogic::ALogic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ALogic::Run()
{
    for(AActor* Actor : Logic)
    {
        if(ILogicInterface* I = Cast<ILogicInterface>(Actor))
        {
            I->OnStart();
            I->Process();
        }
    }
}
