// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// #include "Async/Async.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimExecute.generated.h"

UCLASS()
class TRUDEMO_API ASimExecute : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASimExecute();

	// Overriding the Async Physics Tick function
	virtual void AsyncPhysicsTickActor(float DeltaTime, float SimTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
