// Fill out your copyright notice in the Description page of Project Settings.
#include "LEDBlinkTest.h"
#include "Tasks/Task.h"
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
	maxCycleCount = 1000000;
	cycleCounter = 0;
}

// void ASimExecute::ReceiveLED13Actor(ALED13Actor* Ref) {

// 	this->LED13Ref = Ref;
// }

// Called when the game starts or when spawned
void ASimExecute::BeginPlay()
{
	Super::BeginPlay();

	

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
	

	// AsyncTask(ENamedThreads::AnyHiPriThread, [this]
	// {
	// 	// Simulation kicked off using the below function VVV
	// 	compileAndRun();
	// 	// Updated to call the compileAndRun() function via the FLEDBlinkTest module
	// 	// if(FLEDBlinkTestModule::IsAvailable()){
	// 	// 	UE_LOG(LogTemp, Warning, TEXT("LEDBlinkTestModule is available!"));
	// 	// 	// FLEDBlinkTestModule::Get();
	// 	// 	FLEDBlinkTestModule::compileAndRunLEDBlinkTest();
	// 	// 	// if(FLEDBlinkTestModule::Get()){
	// 	// 	// 	UE_LOG(LogTemp, Warning, TEXT("Got a reference!"));
	// 	// 	// }
	// 	// }
	// });
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

    if (FLEDBlinkTestModule::isSimulationTicking())
    {
		// AsyncTask(ENamedThreads::AnyHiPriThreadNormalTask, [this]()
        // {
		// Step 1: Run an execution tick
		// avrInstruction(runner->cpu);
        // runner->cpu->tick();

		// });

		// UE_LOG(LogTemp, Warning, TEXT("%d"), runner->cpu->cycles);

		// Step 2: Check for updated pin values
        oldLED13Value = newLED13Value;
        newLED13Value = FLEDBlinkTestModule::getLED13();

        if (newLED13Value != oldLED13Value)
        {
            UE_LOG(LogTemp, Warning, TEXT("LED 13 State has changed"));
			UE_LOG(LogTemp, Warning, TEXT("%d"), runner->cpu->cycles);
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

	SimThread = new FSimRunnableThread();



}

void ASimExecute::stopSim(){

	if(SimThread != nullptr){
		SimThread->Thread->Kill();
	}
	// Ensure LED13Ref exists before calling ProcessEvent
	if (LED13Ref && LEDFunction)
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
	
	// UE_LOG(LogTemp, Warning, TEXT("Destroying..."));
	// // runner->~AVRRunner();
	// FLEDBlinkTestModule::stopSimInternal();
}
