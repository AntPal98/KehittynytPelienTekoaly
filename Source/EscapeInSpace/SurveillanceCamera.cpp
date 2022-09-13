// Fill out your copyright notice in the Description page of Project Settings.


#include "SurveillanceCamera.h"

// Sets default values
ASurveillanceCamera::ASurveillanceCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;
  lerpAlpha = 0.0f;
  holdTime = 0.0f;
  rotationSpeed = 1.0f;
  reverseDirection = false;
  holdRemaining = 0.0f;
  detectedPlayer = nullptr;
  isActive = true;
  followMode = false;
  passedTimeSinceStateChange = 0.0f;
  state = CameraState::kSeeking;
  alarmTimeSeconds = DEFAULT_ALARM_TIME_IN_SECONDS;
  analyzeTimeSeconds = DEFAULT_ANALYZE_TIME_IN_SECONDS;
}

// Called when the game starts or when spawned
void ASurveillanceCamera::BeginPlay()
{
	Super::BeginPlay();
	if ( startLookAt == nullptr ) 
	{
			UE_LOG(LogTemp, Error, TEXT("Start look at not set"));
	}
	else 
	{ 
		startPosition = (startLookAt->GetActorLocation() - GetActorLocation()).Rotation(); 
	}
	
	if ( endLookAt == nullptr ) 
	{
		UE_LOG(LogTemp, Error, TEXT("End look at not set"));
	}
	else 
	{ 
		endPosition = (endLookAt->GetActorLocation() - GetActorLocation()).Rotation(); 
	}
	
}

void ASurveillanceCamera::SeekOperation(float DeltaTime)
{
	if (lerpAlpha > 1.0f && holdRemaining <= 0.0f)
	{
		reverseDirection = true;
		holdRemaining = holdTime;
	}
	else if (lerpAlpha < 0.0f && holdRemaining <= 0.0f)
	{
		reverseDirection = false;
		holdRemaining = holdTime;
	}
	if (holdRemaining > 0.0f)
	{
		holdRemaining -= DeltaTime;
		lerpAlpha = FMath::Clamp(lerpAlpha, 0.0f, 1.0f);
	}
	else
	{
		lerpAlpha = FMath::Clamp(lerpAlpha, 0.0f, 1.0f);
		if (reverseDirection) lerpAlpha -= rotationSpeed * DeltaTime;
		else                    lerpAlpha += rotationSpeed * DeltaTime;
		FRotator newRot = FMath::Lerp(startPosition, endPosition, lerpAlpha);

		SetActorRotation(newRot);
	}
}

void ASurveillanceCamera::LookAtPlayer()
{
	// set rotation to match player.
	// Camera model must point along X axis
	FVector cameraToPlayer = detectedPlayer->GetActorLocation() - GetActorLocation();
	SetActorRotation(cameraToPlayer.Rotation());
}

// Called every frame
void ASurveillanceCamera::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);
  
  if ( isActive == false ) return;

  switch (state)
  {
  case CameraState::kSeeking:
	  if (IsPlayerDetected())
	  {
		  SetCameraState(CameraState::kAnalyzing);
	  }
	  else
	  {
		  SeekOperation(DeltaTime);
	  }
	  break;
  case CameraState::kAnalyzing:
	  if (IsPlayerDetected())
	  {
		  LookAtPlayer();
		  passedTimeSinceStateChange += DeltaTime;

		  if (passedTimeSinceStateChange >= analyzeTimeSeconds)
		  {
			  SetCameraState(CameraState::kAlarm);
		  }
	  }
	  else
	  {
		  SetCameraState(CameraState::kSeeking);
	  }
	  break;
  case CameraState::kAlarm:
	  passedTimeSinceStateChange += DeltaTime;

	  if (passedTimeSinceStateChange >= alarmTimeSeconds)
	  {
		  OnRaiseAlarm();
		  SetCameraState(CameraState::kSeeking);
	  }
	  break;
  case CameraState::kNumStates:
	  break;
  default:
	  break;
  }
}

// Called to bind functionality to input
void ASurveillanceCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
/*
void ASurveillanceCamera::OnDisable_Implementation()
{
  
}

void ASurveillanceCamera::OnEnable_Implementation()
{
  
}
*/
void ASurveillanceCamera::Disable()
{
  isActive = false;  
  OnDisable();
}

void ASurveillanceCamera::Enable()
{
  isActive = true;
  OnEnable();
}

void ASurveillanceCamera::OnRaiseAlarm_Implementation()
{
}

void ASurveillanceCamera::OnStateChanged_Implementation(CameraState newState)
{
}

void ASurveillanceCamera::SetCameraState(CameraState newState)
{
	state = newState;
	passedTimeSinceStateChange = 0.0f;
	OnStateChanged(state);
}

void ASurveillanceCamera::SetDetectedPlayer(AActor *player)
{
  
	detectedPlayer = player;
	followMode = (detectedPlayer != nullptr);
	UE_LOG(LogTemp, Log, TEXT("Setting detected player to %sw"), *AActor::GetDebugName(player));
	//if ( detectedPlayer == nullptr )
	//passedTimeSinceStateChange = 0.0;
  
}
bool ASurveillanceCamera::IsPlayerDetected()
{
	// works only if camera is active
	return (detectedPlayer != nullptr) && isActive;
}

