// Fill out your copyright notice in the Description page of Project Settings.

#include "LoadingObjects.h"
#include "ObjectLoader.h"


// Sets default values
AObjectLoader::AObjectLoader()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	values[0] = 0.0; // Framerate with model1
	values[1] = 14.0; // vertice count of model1
	values[2] = 111111.0; // breaker
	values[3] = 0.0; // Framerate with model2
	values[4] = 14.0; // vertice count of model2
	values[5] = 111111.0; // breaker
	values[6] = 0.0; // Framerate with model3
	values[7] = 14.0; // vertice count of model3
	values[8] = 111111.0; // breaker
	directory = "F:/UnrealEngine/InfoToFile";
	filename = "info.csv";

	writeToFile = true;
	nextFrame = 0;
	currentTimer = 0.0f;
	currentFrame = 0.0f;
	refreshTimer = 0.5f;


	CountDownText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Time Till Model Change: "));
	CountDownText->SetHorizontalAlignment(EHTA_Center);
	CountDownText->SetWorldSize(150.0f);
	RootComponent = CountDownText;

	CountDownTimer = 3;

	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	RootComponent = Root;

	//Creating the mesh component and attaching it to the root component
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	mesh->AttachTo(RootComponent);

	static ConstructorHelpers::FObjectFinder <UMaterial> Material_One(TEXT("/Game/Textures/Texture_1_Mat"));
	Mat1 = Material_One.Object; // Jacket

	static ConstructorHelpers::FObjectFinder <UMaterial> Material_Two(TEXT("/Game/Textures/Texture_2_Mat"));
	Mat2 = Material_Two.Object; // Shoes

	static ConstructorHelpers::FObjectFinder <UMaterial> Material_Three(TEXT("/Game/Textures/Texture_3_Mat"));
	Mat3 = Material_Three.Object; // TShirt

	//Grabbing the mesh I'd like to use
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh1(TEXT("/Game/Models/model1"));
	LOD_Data1 = Mesh1.Object->MinLOD;
	VertexCount1 = Mesh1.Object->GetNumVertices(0);
	model1 = Mesh1.Object;// Jacket
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh2(TEXT("/Game/Models/model2"));
	LOD_Data2 = Mesh2.Object->MinLOD;
	VertexCount2 = Mesh2.Object->GetNumVertices(0);
	model2 = Mesh2.Object;// Shoes
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh3(TEXT("/Game/Models/model3"));	
	LOD_Data3 = Mesh3.Object->MinLOD;
	VertexCount3 = Mesh3.Object->GetNumVertices(0);
	model3 = Mesh3.Object;// TShirt

	//Setting the mesh
	modelsLoaded = 0;
	mesh->SetStaticMesh(model1);
}

bool AObjectLoader::SaveStringTextToFile(FString SaveDirectory, FString JoyfulFileName, FString SaveText, bool AllowOverWriting)
{
	//Dir Exists?
	if (!FPlatformFileManager::Get().GetPlatformFile().DirectoryExists(*SaveDirectory))
	{
		//create directory if it not exist
		FPlatformFileManager::Get().GetPlatformFile().CreateDirectory(*SaveDirectory);

		//still could not make directory?
		if (!FPlatformFileManager::Get().GetPlatformFile().DirectoryExists(*SaveDirectory))
		{
			//Could not make the specified directory
			return false;
			//~~~~~~~~~~~~~~~~~~~~~~
		}
	}

	//get complete file path
	SaveDirectory += "/";
	SaveDirectory += JoyfulFileName;

	//No over-writing?
	if (!AllowOverWriting)
	{
		//Check if file exists already
		if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*SaveDirectory))
		{
			//no overwriting
			return false;
		}
	}

	return FFileHelper::SaveStringToFile(SaveText, *SaveDirectory);
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



// Called when the game starts or when spawned
void AObjectLoader::BeginPlay()
{
	Super::BeginPlay();
	UpdateTimerDisplay();
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AObjectLoader::AdvanceTimer, 1.0f, true);
}

void AObjectLoader::FPS(float deltaTime)
{
	if (currentTimer < refreshTimer)
	{
		currentTimer += deltaTime;
		nextFrame++;
	}
	else
	{
		//This code will break if you set your refreshTimer to 0, which makes no sense.
		currentFrame = (float)nextFrame / currentTimer;
		nextFrame = 0;
		currentTimer = 0.0f;
	}
	if (getLoadModel1() == true)
	{
		values[0] = currentFrame;
	}
	else if (getLoadModel2() == true)
	{
		values[3] = currentFrame;
	}
	else if (getLoadModel3() == true)
	{
		values[6] = currentFrame;
		writeToFile = false;
	}
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
		mesh->SetStaticMesh(model1);
		mesh->SetMaterial(2, Mat1);
		modelsLoaded += 1;
	}
	else if (getLoadModel2() == true)
	{
		mesh->SetStaticMesh(model2);
		mesh->SetMaterial(0, Mat2);
		modelsLoaded += 1;
	}
	else if (getLoadModel3() == true)
	{
		mesh->SetStaticMesh(model3);
		mesh->SetMaterial(0, Mat3);
		modelsLoaded += 1;
	}
	
	//SaveStringTextToFile(directory, filename, infoToSave, true);
}

// Called every frame
void AObjectLoader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FPS(DeltaTime);
	
	if (currentFrame >= 100 && writeToFile == false)
	{
		if (modelsLoaded >= 3)
		{
			values[1] = VertexCount1, values[4] = VertexCount2, values[7] = VertexCount3;
			infoToSave = FString::SanitizeFloat(values[0]) + "," + FString::SanitizeFloat(values[1]) + "," + FString::SanitizeFloat(values[2]) + "," + FString::SanitizeFloat(values[3]) + "," + FString::SanitizeFloat(values[4]) + "," + FString::SanitizeFloat(values[5]) + "," + FString::SanitizeFloat(values[6]) + "," + FString::SanitizeFloat(values[7]) + "," + FString::SanitizeFloat(values[8]);
			SaveStringTextToFile(directory, filename, infoToSave, true);
			GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Green, TEXT("WRITING!"));
			writeToFile = true;
		}
	}
}

