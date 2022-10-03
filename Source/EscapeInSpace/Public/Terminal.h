// copyright anssi.grohn@karelia.fi 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Canvas.h"
#include "Engine/CanvasRenderTarget2D.h"
#include "Terminal.generated.h"


const float DEFAULT_LINE_HEIGHT = 50.0f;
const int32 DEFAULT_MAX_LINES = 8;

UCLASS()
class ESCAPEINSPACE_API ATerminal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATerminal();

	UCanvasRenderTarget2D* ScreenTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terminal");
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terminal");
	TArray<FString> Lines;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terminal");
	UFont* Font;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terminal");
	FVector2D ScreenTextureResolution;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terminal");
	int32 MaxLines = DEFAULT_MAX_LINES;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terminal");
	FColor FontColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terminal");
	FLinearColor ClearColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terminal");
	float LineHeight = DEFAULT_LINE_HEIGHT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terminal");
	FName ScreenTextureParamName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terminal");
	int32 IndentationAmount = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terminal");
	float FontScale = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terminal");
	UMaterialInstanceDynamic* MaterialInstance;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void RenderScreen(UCanvas* Canvas, int32 Width, int32 Height);

	UFUNCTION(BlueprintCallable)
	void UpdateText();

	UFUNCTION(BlueprintCallable)
	void AddLine(const FString& line);

};
