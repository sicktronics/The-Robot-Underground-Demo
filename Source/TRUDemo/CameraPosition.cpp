// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPosition.h"

// Sets default values for this component's properties
UCameraPosition::UCameraPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

template<class T>
static T* GetComponentByClass(AActor* Actor)
{
	// Checks whether actor is valid before trying to get component
	return Actor ? Cast<T>(Actor->GetComponentByClass(T::StaticClass())) : nullptr;
}


// Called when the game starts
void UCameraPosition::BeginPlay() {
	Super::BeginPlay();
}

void UCameraPosition::InitConnections() {
	if (IsValid(connectedCameraPosition)) {
		if (GetComponentByClass<UCameraPosition>(connectedCameraPosition)->bindPath(connectionInputDirection, this) == 0) {

			bindPath((CameraDirection) (3 - (uint8)connectionInputDirection),
				GetComponentByClass<UCameraPosition>(connectedCameraPosition));
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("UCameraPosition could not be detecte on connectedCameraPosition"));
		}
	} 
	else {
		UE_LOG(LogTemp, Warning, TEXT("connected Camera Position is null pointer: from CameraPosition %s"), *stateLabel);
	}
}


// Called every frame
void UCameraPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

int UCameraPosition::bindPath(CameraDirection dir, UCameraPosition* bindPos) {
	if (connectionsList.Contains(dir)) {

		UE_LOG(LogTemp, Warning, TEXT("Bind dir already bound. try a different one"));
		return 1;

	} else {
		UE_LOG(LogTemp, Warning, TEXT("Bind attempted: %s to %s"), *stateLabel, *(bindPos->stateLabel));
		connectionsList.Add(dir, bindPos);
		return 0;
	}
}

