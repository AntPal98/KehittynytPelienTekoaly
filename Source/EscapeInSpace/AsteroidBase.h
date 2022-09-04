// copyright anssi.grohn@karelia.fi 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "AsteroidBase.generated.h"


class AGameSaver;

UCLASS()
class ESCAPEINSPACE_API AAsteroidBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAsteroidBase();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent * meshComponent ;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Accept( AGameSaver & saver );
	
};
