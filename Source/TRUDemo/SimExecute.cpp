// Fill out your copyright notice in the Description page of Project Settings.
#include "SimExecute.h"
#include "LEDBlinkTest.h"
#include "Tasks/Task.h"
#include "Kismet/GameplayStatics.h"

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

// Called when the game starts or when spawned
void ASimExecute::BeginPlay()
{
	Super::BeginPlay();

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

	// If the simulation is currently active...
    if (FLEDBlinkTestModule::isSimulationTicking())
    {
		// Check the LED State
        oldLED13Value = newLED13Value;
        newLED13Value = FLEDBlinkTestModule::getLED13();
		// Call ToggleLEDColor if it's changed
        if (newLED13Value != oldLED13Value)
        {
            // Ensure LED13Ref exists before calling ProcessEvent
            if (LED13Ref && LEDFunction)
            {
                Param.IsON = newLED13Value;
                // Move ProcessEvent to the Game Thread
                AsyncTask(ENamedThreads::GameThread, [this]()
                {
                    if (LED13Ref && LEDFunction)
                    {
                        LED13Ref->ProcessEvent(LEDFunction, &Param);
                    }
                });
            }
        }
    }
}

void ASimExecute::startSim(){
	
	// Find all actors of class BPLED13Actor and get a reference to its function of interest 
	if(BPLED13Actor){
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), BPLED13Actor, FoundActors);

		// Ensure at least one actor is found
		if (FoundActors.Num() > 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Found LED 13"));
			LED13Ref = FoundActors[0]; // Assuming the first one found is the one you want

			    // Find relevant BP Function
				FunctionName = TEXT("ToggleLEDColor");
				LEDFunction = LED13Ref->FindFunction(FunctionName);

				// Create and populate the parameter struct
            	Param;
		}
	}
	
	// Create a new dedicated simulation thread
	SimThread = new FSimRunnableThread();
}

void ASimExecute::stopSim(){
	// Shut down the simulation thread
	if(SimThread->Thread != nullptr){
		SimThread->Thread->Kill();

	}
	// Turn off the LED
	if (LED13Ref && LEDFunction && Param.IsON == true)
	{
		Param.IsON = false;
		// Move ProcessEvent to the Game Thread
		AsyncTask(ENamedThreads::GameThread, [this]()
		{
			if (LED13Ref && LEDFunction)
			{
				LED13Ref->ProcessEvent(LEDFunction, &Param);
			}
		});
	}

}
