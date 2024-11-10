// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraMover.h"

template<class T>
static T* GetComponentByClass(AActor* Actor)
{
	// Checks whether actor is valid before trying to get component
	return Actor ? Cast<T>(Actor->GetComponentByClass(T::StaticClass())) : nullptr;
}

// Sets default values for this component's properties
UCameraMover::UCameraMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCameraMover::BeginPlay()
{
	Super::BeginPlay();
	MoveToStateLocation(startPos);
	// ...	
}


// Called every frame
void UCameraMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//WasInputKeyJustPressed(EKeys::C)
	// ...
}

void UCameraMover::CycleAdjStateLocation(FString inputKey) {


	if (IsValid(GetComponentByClass<UCameraPosition>(currentPos)))
	{
		if (GetComponentByClass<UCameraPosition>(currentPos)->connectionsList.Contains(inputKey))
		{
			UCameraPosition* loc = *GetComponentByClass<UCameraPosition>(currentPos)->connectionsList.Find(inputKey);
			
			self->SetActorLocation(loc->GetOwner()->GetActorLocation());
			self->SetActorRotation(loc->GetOwner()->GetActorRotation());

			currentPos = loc->GetOwner();
		} else {
			UE_LOG(LogTemp, Warning, TEXT("input key not found in cameraPosition %s connections list"), *(GetComponentByClass<UCameraPosition>(currentPos)->stateLabel));
		}
		
	} 
	else {
		UE_LOG(LogTemp, Warning, TEXT("Camera Position Component not found"));
	}
}

void UCameraMover::MoveToStateLocation(AActor* loc) {
	if (IsValid(loc))
	{
		self->SetActorLocation(loc->GetActorLocation());
		self->SetActorRotation(loc->GetActorRotation());

		currentPos = loc;
	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("state location does not exist"));
	}
	
}

// void UCameraMover::SetPlayerController(AActor* pc)
// {
// 	playerController = pc;
// }

