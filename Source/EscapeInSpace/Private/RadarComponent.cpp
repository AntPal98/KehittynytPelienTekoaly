// copyright anssi.grohn@karelia.fi 2019


#include "RadarComponent.h"
#include "EngineUtils.h"
#include "AsteroidBase.h"

// Sets default values for this component's properties
URadarComponent::URadarComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	MaxRadarDistance = 30000.0f;
	// ...
}


// Called when the game starts
void URadarComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URadarComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TArray<FVector2D> URadarComponent::GetPointsOnPlane()
{
	TArray<FVector2D> points;

	UpdateTrackedObjects();

	AActor* parent = GetOwner();

	FPlane shipOriantationPlane = FPlane(parent->GetActorLocation(), parent->GetActorUpVector());
	for (auto& a : TrackedObjects)
	{
		AAsteroidBase* asteroid = Cast<AAsteroidBase>(a);

		FVector asteroidLocation = asteroid->meshComponent->GetComponentLocation();

		FVector pointsOnPlane = FVector::PointPlaneProject(asteroidLocation, shipOriantationPlane);
		FVector actorToTrackedObject = pointsOnPlane - parent->GetActorLocation();
		FVector actorToTrackedObjectReal = asteroidLocation - parent->GetActorLocation();

		float x = FVector::DotProduct(actorToTrackedObject, parent->GetActorForwardVector());
		float y = FVector::DotProduct(actorToTrackedObject, parent->GetActorRightVector());

		FVector2D point = FVector2D(x, y);

		if (actorToTrackedObjectReal.Size() < MaxRadarDistance)
		{
			points.Add(point / MaxRadarDistance);
			RealDistanceToTrackedObjects.Add(actorToTrackedObjectReal.Size() / MaxRadarDistance);
		}
		
	}


	return points;
}

void URadarComponent::UpdateTrackedObjects()
{
	TrackedObjects.Empty();
	RealDistanceToTrackedObjects.Empty();
	for (TActorIterator<AActor> actorIt(GetWorld()); actorIt; ++actorIt)
	{
		AActor* a = *actorIt;
		if (a->ActorHasTag(FName("RadarTracked")))
		{
			TrackedObjects.Add(a);
		}
	}
}

float URadarComponent::GetRealDistanceToTrackedObjects(int32 index)
{
	return RealDistanceToTrackedObjects[index];
}

