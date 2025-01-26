// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// #include "Async/Async.h"
#include "SimIndex.h"
#include "LED13Actor.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "GenericPlatform/GenericPlatformProcess.h"
#include "SimExecute.generated.h"

USTRUCT(BlueprintType)
struct FBooleanParameter
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	bool IsON;

	FBooleanParameter() : IsON(false) {}
};

UCLASS()
class TRUDEMO_API ASimExecute : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(BlueprintReadWrite)
	bool oldLED13Value; // Old value of LED 13

	UPROPERTY(BlueprintReadWrite)
	bool newLED13Value; // New value of LED 13

	UPROPERTY()
	AActor* LED13Ref;

	UPROPERTY()
	UFunction* LEDFunction;

	UPROPERTY()
	FName FunctionName;

	UPROPERTY()
	FBooleanParameter Param;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> BPLED13Actor; // Needs to be populated somehow (e.g. by exposing to blueprints as uproperty and setting it there

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

	// UFUNCTION()
	// void ReceiveLED13Actor(ALED13Actor* Ref);

};