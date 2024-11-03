// Fill out your copyright notice in the Description page of Project Settings.


#include "Pin.h"

// Sets default values for this component's properties
UPin::UPin() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	taken = false;
}


// Called when the game starts
void UPin::BeginPlay() {
	Super::BeginPlay();
}


// Called every frame
void UPin::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

