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

		driveLeftMult = (-2*(cpu->GetPinData(driveLDirectionPinNum, tick)) + 1) * ToSpeedDCMotor(cpu->GetPinData(driveLeftPinNum, tick), driveLeftMult);
		driveRightMult = (-2*(cpu->GetPinData(driveRDirectionPinNum, tick)) + 1) * ToSpeedDCMotor(cpu->GetPinData(driveRightPinNum, tick), driveRightMult);

		UE_LOG(LogTemp, Warning, TEXT("Going with driveLeftMult of %f ..."), driveLeftMult);
		UE_LOG(LogTemp, Warning, TEXT("Going with driveRightMult of %f ..."), driveRightMult);

		float deltaPos = (driveLeftMult + driveRightMult) / 2;
		float deltaRot = FMath::Atan((driveRightMult - driveLeftMult) / robotWidth);

		self->SetActorLocation(self->GetActorLocation() + (deltaPos * moveSpeed * DeltaTime) * self->GetActorForwardVector());
		self->SetActorRotation(self->GetActorRotation() + FRotator(0, deltaRot * DeltaTime, 0));

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

