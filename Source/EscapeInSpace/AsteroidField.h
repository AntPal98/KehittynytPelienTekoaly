// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/Map.h"
#include "Components/BoxComponent.h"
#include "AsteroidBase.h"
#include "AsteroidField.generated.h"


UCLASS()
class ESCAPEINSPACE_API AAsteroidField : public AActor
{
	GENERATED_BODY()
public:
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="AsteroidField")
  UBoxComponent *triggerBox; 
public:	
	// Sets default values for this actor's properties
  AAsteroidField();
  //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AsteroidField")
  
  TArray<TWeakObjectPtr<AAsteroidBase>> asteroids;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AsteroidField")
  FRotator minTorque;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AsteroidField")
  FRotator maxTorque;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AsteroidField")
  FVector minForce;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AsteroidField")
  FVector maxForce;
  
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AsteroidField")
  int maxAsteroidsInField;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AsteroidField")
  
  TArray<TSubclassOf<class AAsteroidBase>> asteroidTypes;
  
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
  
	UFUNCTION()
	void OnLeaveArea(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable, Category = "AsteroidField")
	void ClearAllAsteroids();
	
	void SpawnAsteroid( const FTransform & transform, 
						const FVector & velocity,
						const FVector & angularVelocity,
						UClass *asteroidType);
	void SpawnAsteroid();
};
