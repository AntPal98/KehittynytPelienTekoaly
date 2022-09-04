// Fill out your copyright notice in the Description page of Project Settings.


#include "Robot.h"


// Sets default values
ARobot::ARobot()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
  
  //RootComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RootComponent"));
  StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
  
    
  // Load default intended mesh using C++, set to pawn if found.
  static ConstructorHelpers::FObjectFinder<UStaticMesh> robotMesh(TEXT("StaticMesh'/Game/Robot/robotti.robotti'"));
  
  if ( robotMesh.Object )
    StaticMesh->SetStaticMesh(robotMesh.Object);
  
  StaticMesh->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);  
  StaticMesh->SetRelativeLocation(FVector::ZeroVector);
}

// Called when the game starts or when spawned
void ARobot::BeginPlay()
{
	Super::BeginPlay();
  
	
}

// Called every frame
void ARobot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 

}

// Called to bind functionality to input
void ARobot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ARobot::SetMaterialToSeppo()
{
  if ( SeppoMaterial )
    StaticMesh->SetMaterial(0,SeppoMaterial);
  else
    UE_LOG(LogTemp, Warning, TEXT("Cannot set SeppoMaterial!"));
    
}
