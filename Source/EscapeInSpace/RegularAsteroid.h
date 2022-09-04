// copyright anssi.grohn@karelia.fi 2019

#pragma once

#include "CoreMinimal.h"
#include "AsteroidBase.h"
#include "RegularAsteroid.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEINSPACE_API ARegularAsteroid : public AAsteroidBase
{
	GENERATED_BODY()
	
public:
	ARegularAsteroid();
	void Accept( AGameSaver & saver ) override;
	
};
