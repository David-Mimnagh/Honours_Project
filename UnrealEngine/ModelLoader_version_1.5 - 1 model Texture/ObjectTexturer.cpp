// Fill out your copyright notice in the Description page of Project Settings.

#include "TexturingObjects.h"
#include "ObjectTexturer.h"


// Sets default values
AObjectTexturer::AObjectTexturer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Created box component and setting it as the root component
	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	RootComponent = Root;

	//Creating the mesh component and attaching it to the root component
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	mesh->AttachTo(RootComponent);
	MeshScale = FVector(1.0f);
	//Grabbing the mesh I'd like to use
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Game/Models/model2"));

	static ConstructorHelpers::FObjectFinder <UMaterial> Material_Blue(TEXT("/Game/Textures/Texture_3_Mat"));
	Mat1 = Material_Blue.Object;

	//Setting the mesh	
	
	mesh->SetRelativeScale3D(MeshScale);
	mesh->SetWorldScale3D(MeshScale);
	mesh->SetStaticMesh(Mesh.Object);


}

// Called when the game starts or when spawned
void AObjectTexturer::BeginPlay()
{
	Super::BeginPlay();

	mesh->SetMaterial(0, Mat1);

	GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Blue, TEXT("Texture Loading"));
}

// Called every frame
void AObjectTexturer::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

