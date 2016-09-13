// Fill out your copyright notice in the Description page of Project Settings.

#include "LoadingObjects.h"
#include "ObjectLoader.h"


// Sets default values
AObjectLoader::AObjectLoader()
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
	//Setting the mesh
	mesh->SetStaticMesh(Mesh.Object);
	mesh->SetWorldScale3D(MeshScale);
}

// Called when the game starts or when spawned
void AObjectLoader::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObjectLoader::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

