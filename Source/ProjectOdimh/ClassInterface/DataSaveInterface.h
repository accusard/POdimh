// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameFramework/SaveGame.h"
#include "DataSaveInterface.generated.h"

class USaveGame;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDataSaveInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * The interface to any object that wants to implement the saving and loading of game data
 */
class PROJECTODIMH_API IDataSaveInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

    /** Override functions to save and load data */
    virtual void NotifySave(USaveGame* SaveGameData) = 0;
    virtual const bool NotifyLoad(USaveGame* LoadGameData) = 0;
    
};
