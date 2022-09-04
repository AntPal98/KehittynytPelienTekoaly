// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Toggleable.h"
#include "SurveillanceCamera.generated.h"

UCLASS()
class ESCAPEINSPACE_API ASurveillanceCamera : public AToggleable
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASurveillanceCamera();
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera Settings")
  AActor *startLookAt;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera Settings")
  AActor *endLookAt;
  
  FRotator startPosition;
  FRotator endPosition;
  
  float lerpAlpha;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera Settings")
  float rotationSpeed;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera Settings")
  float holdTime;
  float holdRemaining;
  bool  reverseDirection;
 
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera Settings")
  AActor *detectedPlayer;
  
  bool followMode;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera Settings")
  USoundWave *alarmSound;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera Settings")
  bool isActive;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera Settings")
  float TimeToRaiseAlarmFromDetection;
  
  float passedTimeSinceDetection;
  
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
  //UFUNCTION(BlueprintCallable, Category="Surveillance Camera")
	virtual void Disable() override;
	//UFUNCTION(BlueprintCallable, Category="Surveillance Camera")
	virtual void Enable() override;
  
  //UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Surveillance Camera")
	//void OnDisable();
	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Surveillance Camera")
	//void OnEnable();
	
  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Surveillance Camera")
  void OnRaiseAlarm();
  
  UFUNCTION(BlueprintCallable, Category="Surveillance Camera")
  void SetDetectedPlayer(AActor *player);
  UFUNCTION(BlueprintCallable, Category="Surveillance Camera")
  bool IsPlayerDetected();
  
 
};
