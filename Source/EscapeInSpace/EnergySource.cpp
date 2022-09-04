// Fill out your copyright notice in the Description page of Project Settings.


#include "EnergySource.h"


// Sets default values for this component's properties
UEnergySource::UEnergySource()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnergySource::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEnergySource::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



void UEnergySource::AddCharge(float energy)
{
	Energy = FMath::Clamp(Energy+energy, 0.0f, MaxEnergy);
}

float UEnergySource::GetCharge() const
{
	return Energy;
}

float UEnergySource::RequestCharge(float amount )
{
	if ( (Energy - amount) > 0.0f ) 
	{
		AddCharge( -amount);
		return amount;
	}
	else 
	{
		float remaining = Energy;
		AddCharge(-amount);
		return remaining;
	}
}
bool UEnergySource::HasCharge(float amount)
{
	return GetCharge() >= amount;
}
