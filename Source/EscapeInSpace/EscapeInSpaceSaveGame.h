// copyright anssi.grohn@karelia.fi 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "AsteroidBase.h"
#include "EscapeInSpaceSaveGame.generated.h"



enum EAsteroidTypeEnum 
{
	Regular,
	Huge,
	HugeWeird,
	Massive
};

USTRUCT(BlueprintType)
struct FAsteroidStruct 
{	
	GENERATED_BODY()
	
	UPROPERTY()
	FTransform transform;
	UPROPERTY() 
	FVector velocity;
	UPROPERTY()
	FVector angleRotation;
	UPROPERTY()
	int32 type; 
};

/**
 * 
 */
UCLASS()
class ESCAPEINSPACE_API UEscapeInSpaceSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TArray<FAsteroidStruct> asteroids;
	
	UPROPERTY()
	FTransform   playerTransform;
	
	UPROPERTY()
	bool hackedAI;
	
	
	
	
};
