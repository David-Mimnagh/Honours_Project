// Fill out your copyright notice in the Description page of Project Settings.

#include "LoadingObjects.h"
#include "ObjectLoader.h"


// Sets default values
AObjectLoader::AObjectLoader()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	values[0] = 10.0;
	values[1] = 114.0;
	values[2] = 1331.0;

	directory = "F:/UnrealEngine/InfoToFile";
	filename = "info.csv";
	infoToSave = FString::FromInt(values[0]) + "," + FString::FromInt(values[1]) + "," + FString::FromInt(values[2]);

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
	model1 = Mesh1.Object;
	model2 = Mesh2.Object;
	model3 = Mesh3.Object;
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

// Called when the game starts or when spawned
void AObjectLoader::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Blue, infoToSave);

	SaveStringTextToFile(directory, filename, infoToSave, true);
}

// Called every frame
void AObjectLoader::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	//;

}

