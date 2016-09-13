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
	RootComponent = CountDownText;

	CountDownTimer = 3;

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
	--CountDownTimer;
	UpdateTimerDisplay();
	if (CountDownTimer < 1)
	{
		ChangeModel();
		CountDownTimer = 3;
	}
}

void AObjectLoader::ChangeModel()
{
	//Change to a special readout
	CountDownText->SetText(TEXT("Changing model"));
	if (CountDownNumber >= 1)
		CountDownNumber -= 1;
	else
		CountDownNumber = 3;

	setModelLoaded(CountDownNumber);
	if(getLoadModel1() == true)
		mesh->SetStaticMesh(model1);
	else if(getLoadModel2() == true)
		mesh->SetStaticMesh(model2);
	else if (getLoadModel3() == true)
		mesh->SetStaticMesh(model3);

}

// Called when the game starts or when spawned
void AObjectLoader::BeginPlay()
{
	Super::BeginPlay();

	UpdateTimerDisplay();
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AObjectLoader::AdvanceTimer, 1.0f, true);

	GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Blue, TEXT("TESTING"));
}

// Called every frame
void AObjectLoader::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	//;

}

