// copyright anssi.grohn@karelia.fi 2019

#pragma once

#include "CoreMinimal.h"
#include "AsteroidBase.h"
#include "HugeWeirdAsteroid.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEINSPACE_API AHugeWeirdAsteroid : public AAsteroidBase
{
	GENERATED_BODY()
public:

	AHugeWeirdAsteroid();
	
	virtual void BeginPlay() override;
	void Accept(AGameSaver& saver) override;
};
