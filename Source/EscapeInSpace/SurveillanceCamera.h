// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Toggleable.h"
#include "SurveillanceCamera.generated.h"

UENUM( BlueprintType)
enum class CameraState : uint8 {
	kSeeking UMETA(DisplayName="Camera is seeking player"),
	kAnalyzing UMETA(DisplayName = "Camera has detected a player and is still analyzing"),
	kAlarm UMETA(DisplayName = "Camera has detected illegal action and will raise alarm soon"),
	kNumStates  UMETA(DisplayName = "Total number of camera states")
};

const float DEFAULT_ANALYZE_TIME_IN_SECONDS = 5.0f;
const float DEFAULT_ALARM_TIME_IN_SECONDS = 2.0f;

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

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings")
  float analyzeTimeSeconds;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings")
  float alarmTimeSeconds;
  
  float passedTimeSinceStateChange;

  CameraState state;
  
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SeekOperation(float DeltaTime);
	void LookAtPlayer();

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

  UFUNCTION(BlueprintCallable, Category = "Surveillance Camera")
  void SetCameraState(CameraState newState);

  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Surveillance Camera")
  void OnStateChanged(CameraState newState);
  
  UFUNCTION(BlueprintCallable, Category="Surveillance Camera")
  void SetDetectedPlayer(AActor *player);
  UFUNCTION(BlueprintCallable, Category="Surveillance Camera")
  bool IsPlayerDetected();
  
 
};
