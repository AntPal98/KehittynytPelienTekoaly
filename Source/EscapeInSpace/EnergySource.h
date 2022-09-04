// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "EnergySource.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEINSPACE_API UEnergySource : public UStaticMeshComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnergySource();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Energy Settings")
	float  MaxEnergy;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Energy Settings")
	float  Energy;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable, Category = "EnergySource")
	void AddCharge(float charge);
	UFUNCTION(BlueprintCallable, Category = "EnergySource")
	float GetCharge() const;
	UFUNCTION(BlueprintCallable, Category = "EnergySource")
	float RequestCharge( float amount );
	UFUNCTION(BlueprintCallable, Category = "EnergySource")
	bool HasCharge( float amount );
	
};
