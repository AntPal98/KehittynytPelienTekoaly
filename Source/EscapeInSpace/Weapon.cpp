// copyright anssi.grohn@karelia.fi 2019


#include "Weapon.h"
#include "Engine/World.h" // LineTraceSingleByChannel
#include "DrawDebugHelpers.h"
// See DefaultEngine.ini for mapping. Channel ought ot 
// be set with default response to ignore, as most object should not fall in to that category by any default. 
#define EnergyWeaponTraceChannel ECC_GameTraceChannel1

bool
UWeapon::Shoot( AActor * & hitActor )
{
	
	if ( ConsumeBurst() == false ) return false;
	
	FVector direction  = GetOwner()->GetActorForwardVector();
	FHitResult result;
	AActor * actorToIgnore = GetOwner();
	
	FCollisionQueryParams queryParams(FName(TEXT("Energy weapon trace")), true, actorToIgnore);
	UE_LOG(LogTemp, Warning, TEXT("Direction is %s"), *direction.ToString());
	GetWorld()->LineTraceSingleByChannel(	result, 
											GetComponentLocation(), 
											GetComponentLocation()+(direction*Range), 
											EnergyWeaponTraceChannel,  
											queryParams, FCollisionResponseParams::DefaultResponseParam);
	
	hitActor = result.GetActor();
	DrawDebugLine(GetWorld(),GetComponentLocation(),GetComponentLocation()+(direction*Range), FColor::Red, false, 2.0f, 0, 5.0f);
	
	return true;
	
	
}