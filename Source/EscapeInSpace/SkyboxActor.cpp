// copyright anssi.grohn@karelia.fi 2019


#include "SkyboxActor.h"

// Sets default values
ASkyboxActor::ASkyboxActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UProceduralMeshComponent>("ProceduralMesh");
	RootComponent = mesh;


}

// Called when the game starts or when spawned
void ASkyboxActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkyboxActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASkyboxActor::GenerateSphere(int verticalSlices, int horizontalSlices)
{
	float R = 20.0f;
	float angle = 0.0f;
	//float sinAngle;
	//float cosAngle;

	float stepSizeVertical = 180.0f / verticalSlices;
	float stepSizeHorizontal = 360.0f / horizontalSlices;
	float vangle = 90.0f;

	for (int v = 0; v <= verticalSlices; v++, vangle -= stepSizeVertical)
	{
		float hangle = 0.0f;
		float radiusMultiplierAtHeight = 1.0f;
		float height = 0.0f;

		FMath::SinCos(&height, &radiusMultiplierAtHeight, FMath::DegreesToRadians(vangle));

		for (int h = 0; h <= horizontalSlices; h++, hangle += stepSizeHorizontal)
		{
			float X;
			float Y;
			FMath::SinCos(&X, &Y, FMath::DegreesToRadians(hangle));
			Vertices.Add(FVector(X * radiusMultiplierAtHeight, Y * radiusMultiplierAtHeight, height) * R);
			UE_LOG(LogTemp, Warning, TEXT("Added vertex %d: %s"), Vertices.Num() - 1, *Vertices.Last(0).ToString());

			float s = FMath::GetMappedRangeValueClamped(TRange<float>(0.0f, 360.0f), TRange<float>(0.0f, 1.0f), hangle);
			float t = FMath::GetMappedRangeValueClamped(TRange<float>(90.0f, -90.0f), TRange<float>(1.0f, 0.0f), vangle);

			TexCoords.Add(FVector2D(s, t));
		}
	}

	for (int v = 1; v <= verticalSlices; v++)
	{
		for (int h = 0; h <= horizontalSlices; h++)
		{
			int v0 = (v - 1) * (horizontalSlices + 1) + h;
			int v1 = v * (horizontalSlices + 1) + h;
			int v2 = v * (horizontalSlices + 1) + h + 1;
			int v3 = (v - 1) * (horizontalSlices + 1) + h +1;
			Triangles.Add(v0);
			Triangles.Add(v1);
			Triangles.Add(v2);

			Triangles.Add(v0);
			Triangles.Add(v2);
			Triangles.Add(v3);
		}
	}

	//Vertices.Add(FVector(0, 0, R));

	//Vertices.Add(FVector(R, 0, 0));
	//Vertices.Add(FVector(0, R, 0));
	//Vertices.Add(FVector(-R, 0, 0));
	//Vertices.Add(FVector(0, -R, 0));

	//Vertices.Add(FVector(0, 0, -R));

	//TexCoords.Add(FVector2D(0.5,1));

	//TexCoords.Add(FVector2D(0.00, 0.5));
	//TexCoords.Add(FVector2D(0.25, 0.5));
	//TexCoords.Add(FVector2D(0.50, 0.5));
	//TexCoords.Add(FVector2D(0.75, 0.5));

	//TexCoords.Add(FVector2D(0.5, 0.0));

	//// ylapyramidi

	//Triangles.Add(0);
	//Triangles.Add(1);
	//Triangles.Add(2);

	//Triangles.Add(0);
	//Triangles.Add(2);
	//Triangles.Add(3);

	//Triangles.Add(0);
	//Triangles.Add(3);
	//Triangles.Add(4);

	//Triangles.Add(0);
	//Triangles.Add(4);
	//Triangles.Add(1);

	//// alapyramidi

	//Triangles.Add(5);
	//Triangles.Add(2);
	//Triangles.Add(1);

	//Triangles.Add(5);
	//Triangles.Add(3);
	//Triangles.Add(2);

	//Triangles.Add(5);
	//Triangles.Add(4);
	//Triangles.Add(3);

	//Triangles.Add(5);
	//Triangles.Add(1);
	//Triangles.Add(4);

	// luodaan varsinainen mesh
	mesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, TArray<FVector>(), TexCoords, TArray<FLinearColor>(), TArray<FProcMeshTangent>(), true);
}

void ASkyboxActor::PostActorCreated()
{
	GenerateSphere(FMath::Max(VerticalSlices, MIN_VERTICAL_SLICES), FMath::Max(HorizontalSlices, MIN_HORIZONTAL_SLICES));
}



