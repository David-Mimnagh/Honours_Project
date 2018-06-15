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
	directory = "F:/Version8 - Important_numbers - InfoToFile - Texture and multiple objects/TESTING";
	filename = "HIGHPOLYCOUNT5.csv";

	writeToFile = true;
	changeModel = false;
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

	static ConstructorHelpers::FObjectFinder <UMaterial> Material_One(TEXT("/Game/Textures/H_Texture1_Mat"));
	Mat1 = Material_One.Object; // Jacket

	static ConstructorHelpers::FObjectFinder <UMaterial> Material_Two(TEXT("/Game/Textures/H_Texture2_Mat"));
	Mat2 = Material_Two.Object; // Shoes

	static ConstructorHelpers::FObjectFinder <UMaterial> Material_Three(TEXT("/Game/Textures/H_Texture3_Mat"));
	Mat3 = Material_Three.Object; // TShirt

	static ConstructorHelpers::FObjectFinder <UMaterial> Material_Four(TEXT("/Game/Textures/H_Texture4_Mat"));
	Mat4 = Material_Four.Object; // TShirt

	static ConstructorHelpers::FObjectFinder <UMaterial> Material_Five(TEXT("/Game/Textures/H_Texture5_Mat"));
	Mat5 = Material_Five.Object; // TShirt

	//Grabbing the mesh I'd like to use
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh1(TEXT("/Game/Models/H_model1"));
	model1 = Mesh1.Object;// Jacket

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh2(TEXT("/Game/Models/H_model2"));
	model2 = Mesh2.Object;// Shoes

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh3(TEXT("/Game/Models/H_model3"));
	model3 = Mesh3.Object;// TShirt

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh4(TEXT("/Game/Models/H_model4"));
	model4 = Mesh4.Object;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh5(TEXT("/Game/Models/H_model5"));
	model5 = Mesh5.Object;
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
		setLoadModel4(false);
		setLoadModel5(false);
		values[1] = modelNo;
	}
	else if (modelNo == 2)
	{
		setLoadModel1(false);
		setLoadModel2(true);
		setLoadModel3(false);
		setLoadModel4(false);
		setLoadModel5(false);
		values[4] = modelNo;
	}
	else if (modelNo == 3)
	{
		setLoadModel1(false);
		setLoadModel2(false);
		setLoadModel3(true);
		setLoadModel4(false);
		setLoadModel5(false);
		values[7] = modelNo;
	}
	else if (modelNo == 4)
	{
		setLoadModel1(false);
		setLoadModel2(false);
		setLoadModel3(false);
		setLoadModel4(true);
		setLoadModel5(false);
		values[10] = modelNo;
	}
	else if (modelNo == 5)
	{
		setLoadModel1(false);
		setLoadModel2(false);
		setLoadModel3(false);
		setLoadModel4(false);
		setLoadModel5(true);
		values[13] = modelNo;
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
		changeModel = true;
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
	else if (getLoadModel4() == true)
	{
		values[9] = currentFrame;
		writeToFile = false;
	}
	else if (getLoadModel5() == true)
	{
		values[12] = currentFrame;
		writeToFile = false;
	}
	if(changeModel == true)
		ChangeModel(deltaTime);
}

void AObjectLoader::ChangeModel(float deltaTime)
{
	//Change to a special readout
	CountDownText->SetText(TEXT("Changing model"));
	if (CountDownNumber >= 2)
		CountDownNumber -= 1;
	else
		CountDownNumber = 5;

	setModelLoaded(CountDownNumber);
	if (getLoadModel1() == true)
	{
		//timeDelta = time.GetCurrentDeltaTime();
		timeTaken += deltaTime;
		mesh->SetStaticMesh(model1);
		mesh->SetMaterial(2, Mat1);
		values[2] = timeTaken;
		timeTaken = 0.0f;
		modelsLoaded += 1;
	}
	else if (getLoadModel2() == true)
	{
		timeTaken += deltaTime;
		mesh->SetStaticMesh(model2);
		mesh->SetMaterial(0, Mat2);
		values[5] = timeTaken;
		timeTaken = 0.0f;
		modelsLoaded += 1;
	}
	else if (getLoadModel3() == true)
	{
		timeTaken += deltaTime;
		mesh->SetStaticMesh(model3);
		mesh->SetMaterial(0, Mat3);
		values[8] = timeTaken;
		timeTaken = 0.0f;
		modelsLoaded += 1;
	}
	else if (getLoadModel4() == true)
	{
		timeTaken += deltaTime;
		mesh->SetStaticMesh(model4);
		mesh->SetMaterial(0, Mat4);
		values[11] = timeTaken;
		timeTaken = 0.0f;
		modelsLoaded += 1;
	}
	else if (getLoadModel5() == true)
	{
		timeTaken += deltaTime;
		mesh->SetStaticMesh(model5);
		mesh->SetMaterial(0, Mat5);
		values[14] = timeTaken;
		timeTaken = 0.0f;
		modelsLoaded += 1;
	}
	changeModel = false;
	//SaveStringTextToFile(directory, filename, infoToSave, true);
}

// Called every frame
void AObjectLoader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FPS(DeltaTime);
	
	if (currentFrame >= 100 && writeToFile == false)
	{
		if (modelsLoaded >= 5)
		{
			infoToSave = FString::SanitizeFloat(values[0]) + "," + FString::SanitizeFloat(values[1]) + "," + FString::SanitizeFloat(values[2]) + "," + FString::SanitizeFloat(values[3]) + "," + FString::SanitizeFloat(values[4]) + "," + FString::SanitizeFloat(values[5]) + "," + FString::SanitizeFloat(values[6]) + "," + FString::SanitizeFloat(values[7]) + "," + FString::SanitizeFloat(values[8]) + "," + FString::SanitizeFloat(values[9]) + "," + FString::SanitizeFloat(values[10]) + "," + FString::SanitizeFloat(values[11]) + "," + FString::SanitizeFloat(values[12]) + "," + FString::SanitizeFloat(values[13]) + "," + FString::SanitizeFloat(values[14]);
			SaveStringTextToFile(directory, filename, infoToSave, true);
			GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Green, TEXT("WRITING!"));
			writeToFile = true;
			modelsLoaded = 0;
		}
	}
}

