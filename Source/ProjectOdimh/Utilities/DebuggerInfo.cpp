// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "DebuggerInfo.h"

#if !UE_BUILD_SHIPPING
#include "Engine.h"
#endif

// Sets default values
ADebuggerInfo::ADebuggerInfo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    DoNotOverwrite = -1;
    DisplaySeconds = 5.0f;
    Message = FString();
    TextColor = FColor::Green;
    bPrintAboveOld = true;
    Scale = FVector2D(1.f,1.f);
}

// Called when the game starts or when spawned
void ADebuggerInfo::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADebuggerInfo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADebuggerInfo::PrintToScreen(const FString String)
{
    Message = String;
    UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
    GEngine->AddOnScreenDebugMessage(DoNotOverwrite, DisplaySeconds, TextColor, Message, bPrintAboveOld, Scale);
}

