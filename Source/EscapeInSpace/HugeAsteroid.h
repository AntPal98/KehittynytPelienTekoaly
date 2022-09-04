// copyright anssi.grohn@karelia.fi 2019

#pragma once

#include "CoreMinimal.h"
#include "AsteroidBase.h"
#include "HugeAsteroid.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEINSPACE_API AHugeAsteroid : public AAsteroidBase
{
	GENERATED_BODY()
	
public:
	AHugeAsteroid();
	void Accept(AGameSaver & saver ) override;
	
};
