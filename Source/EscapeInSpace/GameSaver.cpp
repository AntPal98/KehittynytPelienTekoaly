// copyright anssi.grohn@karelia.fi 2019


#include "GameSaver.h"
#include "Kismet/GameplayStatics.h"

#include "AsteroidField.h"
#include "AsteroidBase.h"
#include "RegularAsteroid.h"
#include "HugeAsteroid.h"
#include "HugeWeirdAsteroid.h"
#include "MassiveAsteroid.h"
#include "EngineUtils.h"
#include "EscapeInSpace.h"

#define DEFAULT_SAVE_SLOT_NAME "AsteroidFieldSlot"
#define DEFAULT_SAVE_USER_INDEX 0

// Sets default values
AGameSaver::AGameSaver()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameSaver::BeginPlay()
{
	Super::BeginPlay();
  
  
}

// Called every frame
void AGameSaver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameSaver::Save()
{
  SaveGameInstance = Cast<UEscapeInSpaceSaveGame>(UGameplayStatics::CreateSaveGameObject(UEscapeInSpaceSaveGame::StaticClass()));
  if ( SaveGameInstance != nullptr)
  {
  
	UE_LOG(EscapeInSpace, Warning, TEXT("Starting saving..."));
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(),FName("Player"),actors);
	if ( actors.Num() > 0 )
	 {
		AActor *player = actors[0]; 
		SaveGameInstance->playerTransform = player->GetActorTransform();
		
	}
	else
	{
		UE_LOG(EscapeInSpace, Error, TEXT("Player not found for saving."));
	}
	
	//for( TActorIterator<AAsteroidBase> it(GetWorld()); it; ++it)
	TArray<AActor*> asteroidFields;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AAsteroidField::StaticClass(),asteroidFields);
	AAsteroidField * field = Cast<AAsteroidField>(asteroidFields[0]);
    for( auto it : field->asteroids)
	{
        AAsteroidBase *base = it.Get();
		base->Accept(*this);
		//UE_LOG(EscapeInSpace, Warning, TEXT("Saving class type: %s "), *name.ToString()); 		
    }
	if (UGameplayStatics::SaveGameToSlot(SaveGameInstance, DEFAULT_SAVE_SLOT_NAME, DEFAULT_SAVE_USER_INDEX))
    {
		UE_LOG(EscapeInSpace, Warning, TEXT("Saving Finished"));
	}
	else
	{
		UE_LOG(EscapeInSpace, Warning, TEXT("Saving FAILED"));
	}
  }  
		
}

void AGameSaver::Load()
{
  if (UEscapeInSpaceSaveGame* LoadedGame = Cast<UEscapeInSpaceSaveGame>(UGameplayStatics::LoadGameFromSlot(DEFAULT_SAVE_SLOT_NAME, DEFAULT_SAVE_USER_INDEX)))
  {
	 TArray<AActor*> actors;
	 UGameplayStatics::GetAllActorsWithTag(GetWorld(),FName("Player"),actors);
	 TArray<AActor*> asteroidFields;
	 UGameplayStatics::GetAllActorsOfClass(GetWorld(),AAsteroidField::StaticClass(),asteroidFields);
	 AAsteroidField * field = Cast<AAsteroidField>(asteroidFields[0]);

	 
	 // destroy old ones
	 field->ClearAllAsteroids();
	 UE_LOG(EscapeInSpace, Warning, TEXT("Left with #%d asteroids"), field->asteroids.Num());
	  
	 if ( actors.Num() > 0 )
	 {
		AActor *player = actors[0]; 
		player->SetActorTransform(LoadedGame->playerTransform);
	}
	else
	{
		UE_LOG(EscapeInSpace, Error, TEXT("Player not found for loading."));
	}
	 
	 UE_LOG(EscapeInSpace, Warning, TEXT("Loaded slot contains #%d asteroids"),LoadedGame->asteroids.Num());
	 for( FAsteroidStruct & as : LoadedGame->asteroids)
	 {
		UClass* Class = nullptr;
		switch( as.type)
		{
				case EAsteroidTypeEnum::Regular:
					Class = ARegularAsteroid::StaticClass();
				break;
				case EAsteroidTypeEnum::Huge:
					Class = AHugeAsteroid::StaticClass();
				break;
				case EAsteroidTypeEnum::HugeWeird:
					Class = AHugeWeirdAsteroid::StaticClass();
				break;
				case EAsteroidTypeEnum::Massive:
					Class = AMassiveAsteroid::StaticClass();
				break;
		}
		
		if ( Class == nullptr )
		{
			UE_LOG(EscapeInSpace, Error, TEXT("Invalid type found from save game!")); 
		}
		else 
		{
			field->SpawnAsteroid(as.transform, as.velocity, as.angleRotation, Class);		
		}
	 }
      
  }  
		
}

void AGameSaver::Save(AAsteroidBase & as)
{
	
}

void AGameSaver::Save(ARegularAsteroid & as)
{
	FAsteroidStruct a;
	a.transform = as.GetActorTransform();
	a.type = EAsteroidTypeEnum::Regular;
	SaveGameInstance->asteroids.Add(a);
}

void AGameSaver::Save(AHugeAsteroid & as)
{
	FAsteroidStruct a;
	a.transform = as.GetActorTransform();
	a.type = EAsteroidTypeEnum::Huge;
	SaveGameInstance->asteroids.Add(a);
}

void AGameSaver::Save(AHugeWeirdAsteroid & as)
{
	FAsteroidStruct a;
	a.transform = as.GetActorTransform();
	a.type = EAsteroidTypeEnum::HugeWeird;
	SaveGameInstance->asteroids.Add(a);
}
void AGameSaver::Save(AMassiveAsteroid & as)
{
	FAsteroidStruct a;
	a.transform = as.GetActorTransform();
	a.type = EAsteroidTypeEnum::Massive;
	SaveGameInstance->asteroids.Add(a);
}
