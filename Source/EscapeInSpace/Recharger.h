// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "EnergySource.h"
#include "Recharger.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEINSPACE_API URecharger : public UStaticMeshComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URecharger();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Energy Settings")
	UEnergySource * TargetSource;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Energy settings")
	float RechargeRate;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
