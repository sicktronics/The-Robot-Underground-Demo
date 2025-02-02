// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelLoader.h"


// Sets default values for this component's properties
ALevelLoader::ALevelLoader()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryActorTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ALevelLoader::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ALevelLoader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ...
}

// This function takes in the stage and level ids and loads the assosiated level blueprint into the scene
TSubclassOf<class AActor> ALevelLoader::GetLevelToLoad()
{
	return Level;
}

UBaseLevel* ALevelLoader::GetBaseLevelComponent(AActor* obj)
{
	return UFunctions::GetComponentByClass<UBaseLevel>(obj);
}	
