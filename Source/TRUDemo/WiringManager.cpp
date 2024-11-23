// Fill out your copyright notice in the Description page of Project Settings.


#include "WiringManager.h"

AWiringManager::AWiringManager() {
	currState = WiringState::NONE;
}

// Called when the game starts
void AWiringManager::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void AWiringManager::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}


