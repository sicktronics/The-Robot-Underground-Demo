// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SimRunnableThread.h"
#include "HAL/Runnable.h"
#include "LEDBlinkTest.h"
#include "LED13Actor.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "GenericPlatform/GenericPlatformProcess.h"
#include "SimExecute.generated.h"
/*
* Struct to pass the pin state (for now, of LED 13) to the ToggleLEDColor 
* function of the BPLED13Actor
*/
USTRUCT(BlueprintType)
struct FBooleanParameter
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	bool IsON;

	FBooleanParameter() : IsON(false) {}
};

/*
* Class that manages the state of simulation execution
*/
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
	AActor* LED13Ref;	// Reference to our LED 13 Actor

	// Instance of the simulation THREAD
	FSimRunnableThread* SimThread = nullptr;

	UPROPERTY()
	UFunction* LEDFunction;	// Pointer to the LED 13's function

	UPROPERTY()
	FName FunctionName;		// To store the name of the function of interest

	UPROPERTY()
	FBooleanParameter Param; // Blueprint boolean function parameter

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

	// Function for starting the LED Blink Test simulation
	UFUNCTION(BlueprintCallable)
	void startSim();

	// Function for stopping the LED Blink Test simulation
	UFUNCTION(BlueprintCallable)
	void stopSim();

};