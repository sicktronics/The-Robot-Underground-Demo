// Fill out your copyright notice in the Description page of Project Settings.


#include "TempCPU.h"

int TIMEFRAME = 5;

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
	pins.Init("", 20);
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
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*(FPaths::ProjectDir() + pathToFile + filename))) {

		UFunctions::Log("File does not exist");

	} else {

		UFunctions::Log("File exists");
		if (FFileHelper::LoadFileToString(retString, *(FPaths::ProjectDir() + pathToFile + filename))) {
			UFunctions::Log("File successfully loaded into string");
			SplitPinData();
		}
	}
}

void UTempCPU::SplitPinData()
{
	FString Left, Right, Temp;
	Right = retString;
	
	if (retString.Contains(TEXT("**********"))) retString.Split(TEXT("**********"),&Left,&Right);
	for (int j = 0; j < TIMEFRAME; j++) {
		
		for (int i = 0; i < pins.Num(); i++) {
		
			Temp = "pin" + FString::FromInt(i) + " :";

			//UE_LOG(LogTemp, Warning, TEXT("%s"), *Temp);

			if (Right.Contains(Temp)) {
				//UFunctions::Log("Found a pin data set");
				Right.Split((TEXT("%s"), *Temp), &Left, &Right);
				Right.Split(TEXT("\n"), &Left, &Right);
				//UE_LOG(LogTemp, Warning, TEXT("%s"), *Left);
				pins[i] += Left;
			}
	
		}
	}
}	

int UTempCPU::GetPinData(int pinNum, int loc) {

	if (pinNum <= -1 || pinNum > 19)
	{
		UE_LOG(LogTemp, Warning, TEXT("Pin num %i outside of range"), pinNum);
		return 0;
	} 

	const TCHAR* p = *(pins[pinNum]);
	int r = 0;

	// if (*p == "")
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("No pin data found at pin num %i"), pinNum);
	// 	r = 0;
	// } else 
	if (loc < 255 * TIMEFRAME)
	{
		r = p[loc] - '0';
	} else r = 0;
	UE_LOG(LogTemp, Warning, TEXT("CPU Sent value of %i"), r);
	return r;
}
