// Fill out your copyright notice in the Description page of Project Settings.


#include "TempCPU.h"

// Sets default values for this component's properties
UTempCPU::UTempCPU()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTempCPU::BeginPlay()
{
	Super::BeginPlay();

	LoadPinData();
}


// Called every frame
void UTempCPU::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTempCPU::LoadPinData()
{
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(TEXT("C:/Users/lucky/Downloads/NOKILL/package1.txt"))) {

		UFunctions::Log("File does not exist");

	} else {

		UFunctions::Log("File exists");
		if (FFileHelper::LoadFileToString(retString, TEXT("C:/Users/lucky/Downloads/NOKILL/package1.txt"))) {
			UFunctions::Log("File successfully loaded into string");
			SplitPinData();
		}
	}
}

void UTempCPU::SplitPinData()
{
	FString Left, Right;
	Right = retString;
	// if (retString.Contains(TEXT("**********"))) retString.Split(TEXT("**********"),&Left,&Right);
	for (int i = 0; i < pins.Num(); i++) {
		
		FString c = "pin" + FString::FromInt(i) + " :";

		if (Right.Contains(TEXT(c))) {
			UFunctions::Log("Found a pin data set");

		}
	
	}
}	
