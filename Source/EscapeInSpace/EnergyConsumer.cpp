// Fill out your copyright notice in the Description page of Project Settings.


#include "EnergyConsumer.h"


// Sets default values for this component's properties
UEnergyConsumer::UEnergyConsumer() : TargetSource(nullptr)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnergyConsumer::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEnergyConsumer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TargetSource->RequestCharge( DeltaTime * ConstantConsumptionRatePerSecond);
	// ...
}

bool UEnergyConsumer::ConsumeBurst()
{
		if ( TargetSource == nullptr ) return false;
		float level = TargetSource->RequestCharge(BurstConsumptionRate);
		return FMath::IsNearlyEqual(level,BurstConsumptionRate);
		
		
}