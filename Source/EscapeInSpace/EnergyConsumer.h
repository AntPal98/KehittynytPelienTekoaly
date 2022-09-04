// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "EnergySource.h"
#include "EnergyConsumer.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEINSPACE_API UEnergyConsumer : public UStaticMeshComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnergyConsumer();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Energy Consumer")
	UEnergySource * TargetSource;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Energy Consumer")
	float 		BurstConsumptionRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Energy Consumer")
	float 		ConstantConsumptionRatePerSecond;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable, Category="Energy Consumer")
	bool ConsumeBurst();
	
};
