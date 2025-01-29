// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseLevel.h"

// Sets default values for this component's properties
UBaseLevel::UBaseLevel()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBaseLevel::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UBaseLevel::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBaseLevel::SetLevelLoader(ULevelLoader* l)
{
	levelLoader = l;
}

ULevelLoader* UBaseLevel::GetLevelLoader()
{
	if (levelLoader != nullptr)
	{
		return levelLoader;
	} else {
		UE_LOG(LogTemp, Warning, TEXT("Level loader requested but not set in base level"));
		return NULL;
	}
}

