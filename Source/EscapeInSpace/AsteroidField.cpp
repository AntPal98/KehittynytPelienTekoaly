// Fill out your copyright notice in the Description page of Project Settings.


#include "AsteroidField.h"
#include "EscapeInSpace.h"


// Sets default values
AAsteroidField::AAsteroidField()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
  triggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
  RootComponent = triggerBox;
  
}

// Called when the game starts or when spawned
void AAsteroidField::BeginPlay()
{
	Super::BeginPlay();
  // register leave event
	triggerBox->OnComponentEndOverlap.AddDynamic(this, &AAsteroidField::OnLeaveArea);
}

// Called every frame
void AAsteroidField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
  
  if ( asteroids.Num() < maxAsteroidsInField ) 
  {
    SpawnAsteroid();
  }
  // do cleanjup
  TArray<TWeakObjectPtr<AAsteroidBase>> deadbeef;
  for( auto & t : asteroids )
  {
    if ( t.IsValid() == false ) deadbeef.Add(t);
  }
  
  while(deadbeef.Num() > 0 )
  {
      asteroids.Remove(deadbeef[0]);
      deadbeef.RemoveAt(0);
  }
}

void AAsteroidField::OnLeaveArea(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
    FName asteroidTag("Asteroid");
    if ( OtherActor && OtherActor->ActorHasTag(asteroidTag))
    {       
		//UE_LOG(EscapeInSpace, Warning, TEXT("Destroyed asteroid"));
        OtherActor->Destroy();
    }
}

void AAsteroidField::ClearAllAsteroids()
{
	for( auto & a : asteroids)
	{
		if ( a.IsValid() )
			a.Get()->Destroy();
	}
	asteroids.Empty();
}


void AAsteroidField::SpawnAsteroid()
{
	FRotator torque = FMath::Lerp(minTorque,maxTorque, FMath::RandRange(0.0f, 1.0f));
	FVector  force = FMath::Lerp(minForce,maxForce, FMath::RandRange(0.0f, 1.0f));
	FVector boxExtents =  triggerBox->GetScaledBoxExtent()*0.5;
    FVector spawnLocation =  this->GetActorLocation() + 
                                FVector( FMath::RandRange(-boxExtents.X, boxExtents.X),
                                FMath::RandRange(-boxExtents.Y, boxExtents.Y),
								FMath::RandRange(-boxExtents.Z, boxExtents.Z) );
   	FRotator spawnRotation = FRotator::ZeroRotator;
	
	FTransform tr;
	tr.SetLocation(spawnLocation);
	tr.SetRotation(spawnRotation.Quaternion());
	int whichAsteroidType = FMath::RandRange(0,asteroidTypes.Num()-1);
	TSubclassOf<class AActor> asteroidType = asteroidTypes[whichAsteroidType];
	
	if ( asteroidType == nullptr )
	{
		UE_LOG(EscapeInSpace, Error, TEXT("Cannot instantiate, asteroidType IS NULL"));
		return;
	}
	FVector speed = FMath::Lerp( minForce, maxForce, FMath::RandRange(0.0f, 1.0f));
	SpawnAsteroid(tr, speed, FVector::ZeroVector, asteroidType.Get());
}

void AAsteroidField::SpawnAsteroid(	const FTransform & transform, 
									const FVector &   velocity,
									const FVector & angularVelocity,
									UClass *asteroidType)
{
	
	if ( asteroidType == nullptr )
	{
			UE_LOG(EscapeInSpace, Error, TEXT("Cannot instantiate, asteroidType IS NULL"));
			return;
	}
	FActorSpawnParameters spawnParams; 
	spawnParams.Owner = this;
	FRotator spawnRotation = transform.Rotator();
	FVector spawnLocation =  transform.GetLocation();
	  
	TWeakObjectPtr<AAsteroidBase> tmp = GetWorld()->SpawnActor<AAsteroidBase>(asteroidType, spawnLocation, spawnRotation, spawnParams );
	asteroids.Add(tmp); 
	tmp.Get()->Tags.Add(FName("Asteroid"));
	//FRotator torque = FMath::Lerp(minTorque,maxTorque, FMath::RandRange(0.0f, 1.0f));
	//FVector  force = FMath::Lerp(minForce,maxForce, FMath::RandRange(0.0f, 1.0f));

	UStaticMeshComponent * mesh = tmp.Get()->FindComponentByClass<UStaticMeshComponent>();
	UPrimitiveComponent * pc = tmp.Get()->FindComponentByClass<UPrimitiveComponent>();

	//mesh->AddTorqueInDegrees(torque.Euler(), NAME_None, true);
	//mesh->AddForce(force, NAME_None, true); 
	pc->SetPhysicsAngularVelocityInDegrees(angularVelocity, true, NAME_None);
	pc->SetPhysicsLinearVelocity(velocity,  true, NAME_None); 
  
 
}