// Fill out your copyright notice in the Description page of Project Settings.


#include "Robot.h"

// Sets default values for this component's properties
URobot::URobot()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URobot::BeginPlay()
{
	Super::BeginPlay();
	self = GetOwner();
	// ...
	
}


// Called every frame
void URobot::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UTempCPU* cpu = UFunctions::GetComponentByClass<UTempCPU>(CPUObj);
	if (go == true) {

		UE_LOG(LogTemp, Warning, TEXT("Going with sigSpeedMult of %f ..."), sigSpeedMult);
		sigSpeedMult = ToSpeedDCMotor(cpu->GetPinData(drivebasePinNum, tick), sigSpeedMult);
		self->SetActorLocation(self->GetActorLocation() + FVector3d(0, -(sigSpeedMult * moveSpeed * DeltaTime), 0));
		tick++;
	}
}

float URobot::ToSpeedDCMotor(int input, float avg) {

	if (input > 1) input = 1;
	if (input < 0) input = 0;
	float x = ((float)input * 100.0 / 255.0);
	float y = (avg * 100.0 / 255.0);
	UE_LOG(LogTemp, Warning, TEXT("x = %f, y = %f"), x, y);
	return avg + ((float)input * 100.0 / 255.0) - (avg * 100.0 / 255.0);
}

void URobot::SetGo() {
	UFunctions::Log("SetGo completed: GO!!!");
	go = true;
}

