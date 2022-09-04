// copyright anssi.grohn@karelia.fi 2019


#include "Toggleable.h"


// Sets default values
AToggleable::AToggleable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AToggleable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AToggleable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AToggleable::OnEnable_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("No reaction!")) ;
}

void AToggleable::OnDisable_Implementation()
{
	
}

void AToggleable::Enable()
{
  for( auto & t : affectedActors )
  {
	if ( t == this ) continue;
    t->Enable();
  }
  affectedActorsEnabled = true;
  OnEnable();
}

void AToggleable::Disable()
{
  
  for( auto & t : affectedActors )
  {
	if ( t == this ) continue;
    t->Disable();
  }
  affectedActorsEnabled = false;
  OnDisable();
}

void AToggleable::Toggle()
{
    if ( affectedActorsEnabled ) Disable();
    else Enable();
}

