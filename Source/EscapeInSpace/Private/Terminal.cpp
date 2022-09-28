// copyright anssi.grohn@karelia.fi 2019


#include "Terminal.h"

// Sets default values
ATerminal::ATerminal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ScreenMesh"));
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void ATerminal::BeginPlay()
{
	Super::BeginPlay();

	//if (ScreenTextureResolution.X < 100 || ScreenTextureResolution.Y < 100) 
	//{
	//	UE_LOG(LogTemp, Error, TEXT("screen texture resolution is not set in terminal"));
	//	return;
	//}

	//ScreenTexture = UCanvasRenderTarget2D::CreateCanvasRenderTarget2D(GetWorld(), UCanvasRenderTarget2D::StaticClass(), ScreenTextureResolution.X, ScreenTextureResolution.Y);
	
	ScreenTexture->OnCanvasRenderTargetUpdate.AddDynamic(this, &ATerminal::RenderScreen);
	ScreenTexture->ClearColor = ClearColor;

	UMaterialInstanceDynamic* materialInstance = UMaterialInstanceDynamic::Create(Mesh->GetMaterial(0), this);
	Mesh->SetMaterial(0, materialInstance);
	materialInstance->SetTextureParameterValue(ScreenTextureParamName, ScreenTexture);
}

// Called every frame
void ATerminal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATerminal::RenderScreen(UCanvas* Canvas, int32 Width, int32 Height)
{
	Canvas->SetDrawColor(FontColor);
	for (int i = 0; i < Lines.Num(); i++)
	{
		Canvas->DrawText(Font, Lines[i], IndentationAmount, LineHeight + LineHeight * i, FontScale, FontScale, FFontRenderInfo());
	}
}

void ATerminal::UpdateText()
{
	if (ScreenTexture == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Screen texture is not set in terminal"));
		return;
	}

	ScreenTexture->UpdateResource();
}

// Called every frame
void ATerminal::AddLine(const FString& line)
{
	if (Lines.Num() >= MaxLines)
	{
		Lines.RemoveAt(0);
	}
	Lines.Add(line);
	UpdateText();
}

