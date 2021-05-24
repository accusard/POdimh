// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "StoryNode.generated.h"



/**
 * A node that branches to other nodes
 */
UCLASS()
class STORYMODULE_API UStoryNode : public UDataAsset
{
	GENERATED_BODY()
	
public:
    UStoryNode();
	
    UPROPERTY(EditAnywhere)
    UDataAsset* Type;
    
    UPROPERTY(EditAnywhere)
    UDataAsset* Cause;
    
    UPROPERTY(EditAnywhere)
    UDataAsset* Effect;
    
    UPROPERTY()
    TArray<UDataAsset*> Branches;
};

/**
 * A single plot contain an event that can build up into a climax
 */
UCLASS()
class STORYMODULE_API UPlot : public UDataAsset
{
    GENERATED_BODY()
    
public:

};

UCLASS()
class STORYMODULE_API UClimax : public UDataAsset
{
    GENERATED_BODY()
    
public:
    
};

UCLASS()
class STORYMODULE_API UResolution : public UDataAsset
{
    GENERATED_BODY()
    
public:
    
};

UCLASS()
class STORYMODULE_API UCause : public UDataAsset
{
    GENERATED_BODY()
    
public:
    
};

UCLASS()
class STORYMODULE_API UEffect : public UDataAsset
{
    GENERATED_BODY()
    
public:
    
};


UCLASS()
class STORYMODULE_API UEvent : public UDataAsset
{
    GENERATED_BODY()
    
public:
    TArray<UDataAsset*> Factions;
};
