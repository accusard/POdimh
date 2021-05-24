// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "POdimhSaveGame.h"
#include "Engine/GameInstance.h"
#include "Events/EventManager.h"
#include "DebuggerInfo.h"
#include "POdimhGameInstance.generated.h"

class USaveGame;

/**
 * An instance of a game with saving and loading functionalities, a reference to the debug info class,
 * and a reference to the global event component
 */
UCLASS()
class PROJECTODIMH_API UPOdimhGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
    UPOdimhGameInstance(const FObjectInitializer& ObjectInitializer);

    virtual void Init() override;
    
    UPOdimhSaveGame* CreateSaveGameObject();
    
    UFUNCTION(BlueprintCallable)
    void ResetGame(const int32 PlayerIndex);
    UFUNCTION(BlueprintCallable)
    void SaveGame(const FString& SlotName, const int32 PlayerIndex, const bool bNewGameState);
    void LoadGame(const FString& SlotName, const int32 PlayerIndex);
    const bool SafeToSave(const bool bBypassGridState) const;
    
    void LoadActor(AActor* Actor, USaveGame* Data);
    void LoadComponents(AActor* Actor, USaveGame* Data);
    
    UPROPERTY(BlueprintReadOnly)
    UEventManager* EventManager;
    
private:
    void SaveGameToSlot(USaveGame* Data, const FString& SlotName, const int32 Player);

    
};
