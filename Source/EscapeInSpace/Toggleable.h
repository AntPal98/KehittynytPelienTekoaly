// copyright anssi.grohn@karelia.fi 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Toggleable.generated.h"

UCLASS()
class ESCAPEINSPACE_API AToggleable : public APawn
{
	GENERATED_BODY() 
	
public:	
	// Sets default values for this actor's properties
	AToggleable();
	
	// Be careful here! If you build Toggleable chains that have circular references, 
	// execution ends up in to an infinite loop. 
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category="Toggleable")
	TArray<AToggleable *> affectedActors;
	bool affectedActorsEnabled;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category="Toggleable")
  virtual void Enable();
  UFUNCTION(BlueprintCallable, Category="Toggleable")
  virtual void Disable();
  UFUNCTION(BlueprintCallable, Category="Toggleable")
  virtual void Toggle();
  
  UFUNCTION(BlueprintNativeEvent)
  void OnEnable();
  
  UFUNCTION(BlueprintNativeEvent)
  void OnDisable();
	
	
};
