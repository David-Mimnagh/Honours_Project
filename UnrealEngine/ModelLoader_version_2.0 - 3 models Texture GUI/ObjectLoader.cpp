// Fill out your copyright notice in the Description page of Project Settings.

#include "LoadingObjects.h"
#include "ObjectLoader.h"


// Sets default values
AObjectLoader::AObjectLoader()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CountDownText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Time Till Model Change: "));
	CountDownText->SetHorizontalAlignment(EHTA_Center);
	CountDownText->SetWorldSize(150.0f);
	CountDownText->SetTextRenderColor(FColor::Blue);
	RootComponent = CountDownText;

	CountDownTimer = 3;
	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	RootComponent = Root;

	//Creating the mesh component and attaching it to the root component
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	mesh->AttachTo(RootComponent);

	//Grabbing the texture for each mesh
	static ConstructorHelpers::FObjectFinder <UMaterial> Material_One(TEXT("/Game/Textures/Texture_1_Mat"));
	Mat1 = Material_One.Object; // Jacket

	static ConstructorHelpers::FObjectFinder <UMaterial> Material_Two(TEXT("/Game/Textures/Texture_2_Mat"));
	Mat2 = Material_Two.Object; // Shoes

	static ConstructorHelpers::FObjectFinder <UMaterial> Material_Three(TEXT("/Game/Textures/Texture_3_Mat"));
	Mat3 = Material_Three.Object; // TShirt

	//Grabbing the mesh I'd like to use
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh1(TEXT("/Game/Models/model1"));
	model1 = Mesh1.Object; //   Jacket

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh2(TEXT("/Game/Models/model2"));
	model2 = Mesh2.Object; //	Shoes

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh3(TEXT("/Game/Models/model3"));
	model3 = Mesh3.Object; //   TShirt
	
}
void AObjectLoader::setModelLoaded(int modelNo)
{
	if (modelNo == 1)
	{
		setLoadModel1(true);
		setLoadModel2(false);
		setLoadModel3(false);
	}
	else if (modelNo == 2)
	{
		setLoadModel1(false);
		setLoadModel2(true);
		setLoadModel3(false);
	}
	else if (modelNo == 3)
	{
		setLoadModel1(false);
		setLoadModel2(false);
		setLoadModel3(true);
	}
}

void AObjectLoader::UpdateTimerDisplay()
{
	CountDownText->SetText(FString::FromInt(FMath::Max(CountDownTimer, 0)));
}

void AObjectLoader::AdvanceTimer()
{
	UpdateTimerDisplay();
	if (CountDownTimer < 1)
	{
		ChangeModel();
		CountDownTimer = 3;
	}
	--CountDownTimer;
}

void AObjectLoader::ChangeModel()
{
	//Change to a special readout
	CountDownText->SetText(TEXT("Changing model"));
	if (CountDownNumber >= 2)
		CountDownNumber -= 1;
	else
		CountDownNumber = 3;

	setModelLoaded(CountDownNumber);

	if (getLoadModel1() == true) 
	{
		GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Blue, TEXT("Loading Jacket "));
		mesh->SetStaticMesh(model1);
		mesh->SetMaterial(2, Mat1);
	}

	if (getLoadModel2() == true)
	{
		GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Blue, TEXT("Loading Shoes "));
		mesh->SetStaticMesh(model2);
		mesh->SetMaterial(0, Mat2);
	}

	if (getLoadModel3() == true)
	{
		GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Blue, TEXT("Loading TShirt "));
		mesh->SetStaticMesh(model3);
		mesh->SetMaterial(0, Mat3);
	}
	GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Blue, TEXT("Current Model Number: " + FString::FromInt(CountDownNumber)));
}

// Called when the game starts or when spawned
void AObjectLoader::BeginPlay()
{
	Super::BeginPlay();
	UpdateTimerDisplay();
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AObjectLoader::AdvanceTimer, 1.0f, true);
	//GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Blue, TEXT("Current Model Number: " + FString::FromInt(CountDownNumber)));
}

// Called every frame
void AObjectLoader::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

