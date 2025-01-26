// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "SimExecute.h"

// Sets default values
ASimExecute::ASimExecute()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// The next two lines are to set up physics ticks
	PrimaryActorTick.TickGroup = TG_PrePhysics;

	bAsyncPhysicsTickEnabled = true; //You can access this in here

	// Initialize members
	oldLED13Value = 0;
	newLED13Value = 0;
	LED13Ref = nullptr;
}

// void ASimExecute::ReceiveLED13Actor(ALED13Actor* Ref) {

// 	this->LED13Ref = Ref;
// }

// Called when the game starts or when spawned
void ASimExecute::BeginPlay()
{
	Super::BeginPlay();

	AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [this]
	{
		// Simulation kicked off using the below function VVV
		compileAndRun();

	});
	
	// Find all actors of class MyBlueprintActor (replace with your Blueprint's class name)
	if(BPLED13Actor){
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), BPLED13Actor, FoundActors);

		// Ensure at least one actor is found
		if (FoundActors.Num() > 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Found LED 13"));
			LED13Ref = FoundActors[0]; // Assuming the first one found is the one you want

			    // Find relevant BP Function
				FunctionName = TEXT("ToggleLEDColor"); // Replace with the actual function name
				LEDFunction = LED13Ref->FindFunction(FunctionName);

				// Create and populate the parameter struct
            	Param;
		}
	}
}

// Called every frame
void ASimExecute::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called every physics tick
void ASimExecute::AsyncPhysicsTickActor(float DeltaTime, float SimTime)
{
	Super::AsyncPhysicsTickActor(DeltaTime, SimTime);
	ReceiveAsyncPhysicsTick(DeltaTime, SimTime);

		if(runner != nullptr && simBeginTicking == true) {
			oldLED13Value = newLED13Value;
			newLED13Value = led13;
			if(newLED13Value != oldLED13Value){
				UE_LOG(LogTemp, Warning, TEXT("LED 13 State has changed"));
				// Check for valid LED Ref - then pass it the bool
				if(LED13Ref) {
					if (LEDFunction)
					{
						// Set your desired boolean value
						Param.IsON = newLED13Value; 

						// If the function takes parameters, create a struct matching the parameter layout
						LED13Ref->ProcessEvent(LEDFunction, &Param);
					}
				}
			}
			// UE_LOG(LogTemp, Warning, TEXT("LED 13 State: %d"), led13);

		}
	// }
}

