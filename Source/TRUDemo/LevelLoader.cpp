// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelLoader.h"


// Sets default values for this component's properties
ULevelLoader::ULevelLoader()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULevelLoader::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULevelLoader::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// This function takes in the stage and level ids and loads the assosiated level blueprint into the scene
TSubclassOf<class AActor> ULevelLoader::GetLevel()
{
	return MyClassType;
}

UBaseLevel* ULevelLoader::GetBaseLevelComponent(AActor* obj)
{
	return UFunctions::GetComponentByClass<UBaseLevel>(obj);
}	
