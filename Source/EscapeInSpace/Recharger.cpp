// Fill out your copyright notice in the Description page of Project Settings.


#include "Recharger.h"


// Sets default values for this component's properties
URecharger::URecharger() : 
		TargetSource(nullptr), 
		RechargeRate(0.0f)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URecharger::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URecharger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if ( TargetSource != nullptr )
	{
			TargetSource->AddCharge(RechargeRate*DeltaTime);
	}

	// ...
}

