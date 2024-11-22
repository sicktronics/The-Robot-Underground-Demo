// Fill out your copyright notice in the Description page of Project Settings.

#include "Pin.h"

#include "Logging/StructuredLog.h"

// Sets default values for this component's properties
APin::APin() {
	taken = false;

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


// Called when the game starts
void APin::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void APin::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}


AMalePin::AMalePin() {}

