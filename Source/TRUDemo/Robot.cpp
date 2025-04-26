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
	
	initRotation = self->GetActorRotation();
	// ...
	
}


// Called every frame
void URobot::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

FRotator URobot::GetMovementVector(float DeltaTime)
{


	UTempCPU* cpu = UFunctions::GetComponentByClass<UTempCPU>(self);
	if (go == true) {

		driveLeftMult = (cpu->GetPinData(leftForwardPin, tick) - cpu->GetPinData(leftBackwardPin, tick)) * ToSpeedDCMotor(cpu->GetPinData(driveLeftPin, tick), driveLeftMult);
		driveRightMult = (cpu->GetPinData(rightForwardPin, tick) - cpu->GetPinData(rightBackwardPin, tick)) * ToSpeedDCMotor(cpu->GetPinData(driveRightPin, tick), driveRightMult);

		// UE_LOG(LogTemp, Warning, TEXT("Going with driveLeftMult of %f ..."), driveLeftMult);
		// UE_LOG(LogTemp, Warning, TEXT("Going with driveRightMult of %f ..."), driveRightMult);

		float deltaPos = (driveLeftMult + driveRightMult) / 2;
		float deltaRot = FMath::Atan((driveRightMult - driveLeftMult) / robotWidth);

		tick++;
		return initRotation + FRotator(0, deltaRot * DeltaTime, 0);
		//return self->GetActorLocation() + (deltaPos * moveSpeed * DeltaTime) * self->GetActorForwardVector();
		
	}
	else {
		return initRotation;
	}
}

float URobot::GetDriveSpeed(float DeltaTime)
{
	UTempCPU* cpu = UFunctions::GetComponentByClass<UTempCPU>(self);
	if (go == true) {

		driveLeftMult = (cpu->GetPinData(leftForwardPin, tick) - cpu->GetPinData(leftBackwardPin, tick)) * ToSpeedDCMotor(cpu->GetPinData(driveLeftPin, tick), driveLeftMult);
		driveRightMult = (cpu->GetPinData(rightForwardPin, tick) - cpu->GetPinData(rightBackwardPin, tick)) * ToSpeedDCMotor(cpu->GetPinData(driveRightPin, tick), driveRightMult);

		UE_LOG(LogTemp, Warning, TEXT("Going with driveLeftMult of %f ..."), driveLeftMult);
		UE_LOG(LogTemp, Warning, TEXT("Going with driveRightMult of %f ..."), driveRightMult);

		float deltaPos = (driveLeftMult + driveRightMult) / 2;
		float deltaRot = FMath::Atan((driveRightMult - driveLeftMult) / robotWidth);

		tick++;
		//return self->GetActorRotation() + FRotator(0, deltaRot * DeltaTime, 0);
		
		float result = (float)(deltaPos * moveSpeed);
		UE_LOG(LogTemp, Warning, TEXT("%f"), result);
		return result;
		
	} else
	{
		return 0;
	}
}

float URobot::ToSpeedDCMotor(int input, float avg) {

	if (input > 1) input = 1;
	if (input < 0) input = 0;
	float x = ((float)input * 100.0 / 255.0);
	float y = (avg * 100.0 / 255.0);
	UE_LOG(LogTemp, Warning, TEXT("input = %f, avg = %f"), x, y);
	return avg + ((float)input * 100.0 / 255.0) - (avg * 100.0 / 255.0);
}

void URobot::SetGo() {
	UFunctions::Log("SetGo completed: GO!!!");
	go = true;
}