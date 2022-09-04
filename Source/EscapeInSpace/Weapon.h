// copyright anssi.grohn@karelia.fi 2019

#pragma once

#include "CoreMinimal.h"
#include "EnergyConsumer.h"
#include "Weapon.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEINSPACE_API UWeapon : public UEnergyConsumer
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float Range;
	UFUNCTION( BlueprintCallable, Category = "Weapon")
	bool Shoot(  AActor * & hitActor  );
	
	
};
