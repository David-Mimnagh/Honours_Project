// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ObjectLoader.generated.h"

UCLASS()
class LOADINGOBJECTS_API AObjectLoader : public AActor
{
	GENERATED_BODY()
		
		int values [10];
		FString directory, filename;
		FString infoToSave;
public:	
	// Sets default values for this actor's properties
	AObjectLoader();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool SaveStringTextToFile(FString SaveDirectory, FString FileName, FString SaveText, bool AllowOverWriting);
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//APlayerController* playerController;
	//Changed to a UBoxComponent
	UPROPERTY(EditAnywhere)
		UBoxComponent* Root;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent*  mesh;
	UPROPERTY(EditAnywhere)
		UStaticMesh*  model1;
	UPROPERTY(EditAnywhere)
		UStaticMesh* model2;
	UPROPERTY(EditAnywhere)
		UStaticMesh* model3;

	
};