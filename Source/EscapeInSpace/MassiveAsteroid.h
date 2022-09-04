// copyright anssi.grohn@karelia.fi 2019

#pragma once

#include "CoreMinimal.h"
#include "AsteroidBase.h"
#include "MassiveAsteroid.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEINSPACE_API AMassiveAsteroid : public AAsteroidBase
{
	GENERATED_BODY()
	
	AMassiveAsteroid();
	void Accept(AGameSaver& saver) override;
	
};
