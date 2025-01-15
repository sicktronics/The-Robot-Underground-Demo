// Fill out your copyright notice in the Description page of Project Settings.


#include "SimExecute.h"

// Sets default values
ASimExecute::ASimExecute()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// The next two lines are to set up physics ticks
	PrimaryActorTick.TickGroup = TG_PrePhysics;

	bAsyncPhysicsTickEnabled = true; //You can access this in here

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
	// if(GEngine)
    //  GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Physics tick, biotch!"));

	// PhysicsTickWorker(DeltaTime); //Function where you keep all your physics tasks
	Super::AsyncPhysicsTickActor(DeltaTime, SimTime);
	ReceiveAsyncPhysicsTick(DeltaTime, SimTime);
}

