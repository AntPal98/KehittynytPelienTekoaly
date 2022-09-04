// copyright anssi.grohn@karelia.fi 2019


#include "HugeWeirdAsteroid.h"
#include "GameSaver.h"

AHugeWeirdAsteroid::AHugeWeirdAsteroid()
{
 meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    
  
  static ConstructorHelpers::FObjectFinder<UStaticMesh> asteroidMesh(TEXT("StaticMesh'/Game/Asteroids/asteroidi.asteroidi'"));
  
  if ( asteroidMesh.Object )
    meshComponent->SetStaticMesh(asteroidMesh.Object);
  
  //static ConstructorHelpers::FObjectFinder<UMaterialInterface> asteroidMaterial(TEXT("MaterialInstanceConstant'/Game/Asteroids/StaticAsteroidMaterial.StaticAsteroidMaterial'"));
  static ConstructorHelpers::FObjectFinder<UMaterialInterface> asteroidMaterial(TEXT("Material'/Game/Asteroids/AsteroidMaterial.AsteroidMaterial'"));
	
  if ( asteroidMaterial.Object)
	meshComponent->SetMaterial(0,asteroidMaterial.Object); 
  
  meshComponent->SetSimulatePhysics(true);
  meshComponent->SetEnableGravity(false);
  meshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
  
  SetActorScale3D(FVector(10.0f,10.0f,10.0f));
 
}

void AHugeWeirdAsteroid::BeginPlay() 
{
		
}
	
void AHugeWeirdAsteroid::Accept(AGameSaver& saver)
{
	saver.Save(*this);
}
