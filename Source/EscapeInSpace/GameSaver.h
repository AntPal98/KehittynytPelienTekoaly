// copyright anssi.grohn@karelia.fi 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EscapeInSpaceSaveGame.h"
#include "GameSaver.generated.h"

class AAsteroidBase;
class ARegularAsteroid;
class AHugeAsteroid;
class AHugeWeirdAsteroid;
class AMassiveAsteroid;

UCLASS()
class ESCAPEINSPACE_API AGameSaver : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameSaver();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void Save();
	UFUNCTION(BlueprintCallable)
	void Load();
	UEscapeInSpaceSaveGame *SaveGameInstance;
	void Save( AAsteroidBase & a );
	void Save( ARegularAsteroid & a);
	void Save( AHugeAsteroid  & a);
	void Save( AHugeWeirdAsteroid &a  );
	void Save( AMassiveAsteroid &a  );
};
