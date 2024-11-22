// Fill out your copyright notice in the Description page of Project Settings.


#include "Wireable.h"

// Sets default values
AWireable::AWireable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWireable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWireable::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

APin* AWireable::getPin(int i) const {
	if (i < 0 || i >= pins.Num()) { return nullptr; }
	return pins[i];
}

