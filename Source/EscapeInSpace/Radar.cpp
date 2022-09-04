// copyright anssi.grohn@karelia.fi 2019


#include "Radar.h"


// Sets default values
ARadar::ARadar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARadar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARadar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

