// Fill out your copyright notice in the Description page of Project Settings.

#include "LoadingObjects.h"
#include "ObjectLoader.h"


// Sets default values
AObjectLoader::AObjectLoader()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	values[0] = 10.0f;
	values[1] = 1114.0f;
	values[2] = 13431.0f;
	directory = "G:/E-HD/UNI/4th Year/Honours/Programs/Unreal/Version7 - Important_InfoToFile_1Object";
	filename = "info.csv";
	
	writeToFile = false;
	nextFrame = 0;
	currentTimer = 0.0f;
	currentFrame = 0.0f;
	refreshTimer = 0.5f;

	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	RootComponent = Root;

	//Creating the mesh component and attaching it to the root component
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	mesh->AttachTo(RootComponent);
	//Grabbing the mesh I'd like to use
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh1(TEXT("/Game/Models/model1"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh2(TEXT("/Game/Models/model2"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh3(TEXT("/Game/Models/model3"));


	//Setting the mesh
	LOD_Data = Mesh3.Object->MinLOD;
	VertexCount = Mesh3.Object->GetNumVertices(0);
	model1 = Mesh1.Object;
	model2 = Mesh2.Object;
	model3 = Mesh3.Object;
	mesh->SetStaticMesh(model3);
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

// Called when the game starts or when spawned
void AObjectLoader::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Blue, infoToSave);
	GetWorld()->Exec(GetWorld(), TEXT("stat fps"));
	SaveStringTextToFile(directory, filename, infoToSave, true);
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
}

// Called every frame
void AObjectLoader::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Blue, FString::SanitizeFloat(VertexCount));
	
	
	FPS(DeltaTime);
	values[1] = VertexCount;

	if (currentFrame >= 100 && writeToFile == false)
	{
		values[0] = currentFrame;
		infoToSave = FString::FromInt(values[0]) + "," + FString::FromInt(values[1]) + "," + FString::FromInt(values[2]);
		SaveStringTextToFile(directory, filename, infoToSave, true);
		writeToFile = true;
	}
}

