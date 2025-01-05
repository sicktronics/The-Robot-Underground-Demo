// Fill out your copyright notice in the Description page of Project Settings.


#include "Functions.h"

// Sets default values for this component's properties
UFunctions::UFunctions()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}
void UFunctions::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}
void UFunctions::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UFunctions::Log(const char* msg, ...)
{
	//UE_LOG(LogTemp, Warning, TEXT("Attempting log"));
	UE_LOG(LogTemp, Warning, TEXT("%hs"), msg);
}

