// copyright anssi.grohn@karelia.fi 2019


#include "AsteroidBase.h"
#include "GameSaver.h"

// Sets default values
AAsteroidBase::AAsteroidBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
  Tags.Add(FName("Asteroid"));
}

// Called when the game starts or when spawned
void AAsteroidBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAsteroidBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAsteroidBase::Accept( AGameSaver & saver )
{
	saver.Save(*this);
}
