// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ObjectLoader.generated.h"

UCLASS()
class LOADINGOBJECTS_API AObjectLoader : public AActor
{
	GENERATED_BODY()
		int32 CountDownTimer;
		int32 CountDownNumber;
		bool loadModel1, loadModel2, loadModel3;
public:	
	// Sets default values for this actor's properties
	AObjectLoader();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool getLoadModel1() { return loadModel1; }
	void setLoadModel1(bool model1) { loadModel1 = model1; }

	bool getLoadModel2() { return loadModel2; }
	void setLoadModel2(bool model2) { loadModel2 = model2; }

	bool getLoadModel3() { return loadModel3; }
	void setLoadModel3(bool model3) { loadModel3 = model3; }

	void setModelLoaded(int modelNo);

	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	void UpdateTimerDisplay();
	void AdvanceTimer();

	void ChangeModel();

	FTimerHandle CountdownTimerHandle;
	UTextRenderComponent* CountDownText;
	//APlayerController* playerController;
	//Changed to a UBoxComponent
	UPROPERTY(EditAnywhere)
		UBoxComponent* Root;

	UPROPERTY(EditAnywhere)
		UMaterial* Mat1;
	UPROPERTY(EditAnywhere)
		UMaterial* Mat2;
	UPROPERTY(EditAnywhere)
		UMaterial* Mat3;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent*  mesh;
	UPROPERTY(EditAnywhere)
		UStaticMesh*  model1;
	UPROPERTY(EditAnywhere)
		UStaticMesh* model2;
	UPROPERTY(EditAnywhere)
		UStaticMesh* model3;

	
};
