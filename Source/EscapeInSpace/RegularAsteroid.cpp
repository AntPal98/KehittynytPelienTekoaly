// copyright anssi.grohn@karelia.fi 2019


#include "RegularAsteroid.h"
#include "GameSaver.h"




ARegularAsteroid::ARegularAsteroid()
{
  
  meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    
  
  static ConstructorHelpers::FObjectFinder<UStaticMesh> asteroidMesh(TEXT("StaticMesh'/Game/Asteroids/asteroidi.asteroidi'"));
  
  if ( asteroidMesh.Object )
    meshComponent->SetStaticMesh(asteroidMesh.Object);
  
  static ConstructorHelpers::FObjectFinder<UMaterialInterface> asteroidMaterial(TEXT("Material'/Game/Asteroids/AsteroidMaterial.AsteroidMaterial'"));
  if ( asteroidMaterial.Object)
	meshComponent->SetMaterial(0,asteroidMaterial.Object); 
  
  meshComponent->SetSimulatePhysics(true);
  meshComponent->SetEnableGravity(false);	
  meshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform); 

  //StaticMesh->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);  
  //StaticMesh->SetRelativeLocation(FVector::ZeroVector);
  
	
}

void ARegularAsteroid::Accept(AGameSaver& saver)
{
	saver.Save(*this);
}
