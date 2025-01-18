// Fill out your copyright notice in the Description page of Project Settings.


#include "SimIndex.h"

// Sets default values
ASimIndex::ASimIndex()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASimIndex::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASimIndex::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASimIndex::CompileAndRun()
{
	// AVRRunner *runner = new AVRRunner("hi");
	// bool test = isTwoWordInstruction(10);
}

void ASimIndex::ExecuteProgram()
{
	
}