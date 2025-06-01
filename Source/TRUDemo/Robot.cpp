// Fill out your copyright notice in the Description page of Project Settings.


#include "Robot.h"

// Sets default values for this component's properties
URobot::URobot()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void URobot::BeginPlay()
{
	Super::BeginPlay();
	self = GetOwner();
	
	initRotation = self->GetActorRotation();
	go = false;
}


// Called every frame
void URobot::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	UTempCPU* cpu = UFunctions::GetComponentByClass<UTempCPU>(self);
	if (go && !cpu->IsValidTick(tick)) go = false;
	
	if (go) UpdateValues();
}

FRotator URobot::GetMovementVector(float DeltaTime) const {
	UTempCPU* cpu = UFunctions::GetComponentByClass<UTempCPU>(self);
	if (go) {
		float driveLeftMult = (cpu->GetPinData(leftForwardPin, tick) - cpu->GetPinData(leftBackwardPin, tick)) * leftMotorSpeed;
		float driveRightMult = (cpu->GetPinData(rightForwardPin, tick) - cpu->GetPinData(rightBackwardPin, tick)) * rightMotorSpeed;

		float deltaPos = (driveLeftMult + driveRightMult) / 2;
		float deltaRot = moveSpeed*(driveLeftMult - driveRightMult)/robotWidth;

		return FRotator(0, deltaRot * DeltaTime, 0);
		
	}
	else {
		return FRotator(0, 0, 0);
	}
}

float URobot::GetDriveSpeed(float DeltaTime) const {
	UTempCPU* cpu = UFunctions::GetComponentByClass<UTempCPU>(self);
	if (go) {
		float driveLeftMult = (cpu->GetPinData(leftForwardPin, tick) - cpu->GetPinData(leftBackwardPin, tick)) * leftMotorSpeed;
		float driveRightMult = (cpu->GetPinData(rightForwardPin, tick) - cpu->GetPinData(rightBackwardPin, tick)) * rightMotorSpeed;

		float deltaPos = (driveLeftMult + driveRightMult) / 2;
		float deltaRot = FMath::Atan((driveRightMult - driveLeftMult) / robotWidth);
		
		return (float)(deltaPos * moveSpeed);
		
	} else
	{
		return 0;
	}
}

void URobot::UpdateValues() {
	tick++;

	UTempCPU* cpu = UFunctions::GetComponentByClass<UTempCPU>(self);
	UpdateMotorSpeed(cpu->GetPinData(driveLeftPin, tick), leftMotorSpeed, lastLeftMults);
	UpdateMotorSpeed(cpu->GetPinData(driveRightPin, tick), rightMotorSpeed, lastRightMults);
}

void URobot::UpdateMotorSpeed(int input, float& avg, TArray<int32>& prev) const {
	if (input > 1) input = 1;
	if (input < 0) input = 0;

	avg += 1.0/ROBOT_BUF_SIZE * (input - prev[tick % ROBOT_BUF_SIZE]);
	prev[tick % ROBOT_BUF_SIZE] = input;
}

void URobot::SetGo() {
	UFunctions::Log("SetGo completed: GO!!!");

	lastLeftMults.Init(0, 255);
	lastRightMults.Init(0, 255);
	
	UFunctions::GetComponentByClass<UTempCPU>(self)->LoadPinData();	

	tick = 0;
	go = true;
}

void URobot::DebugPrint() const {
	if (!go) {
		UE_LOG(LogTemp, Warning, TEXT("setGo = false"));
		return;
	}

	UTempCPU* cpu = UFunctions::GetComponentByClass<UTempCPU>(self);
	float driveLeftMult = (cpu->GetPinData(leftForwardPin, tick) - cpu->GetPinData(leftBackwardPin, tick)) * leftMotorSpeed;
	float driveRightMult = (cpu->GetPinData(rightForwardPin, tick) - cpu->GetPinData(rightBackwardPin, tick)) * rightMotorSpeed;

	float deltaPos = (driveLeftMult + driveRightMult) / 2;
	float deltaRot = moveSpeed*(driveLeftMult - driveRightMult)/robotWidth;

	UE_LOG(LogTemp, Warning, TEXT("driveLeftMult = %f, driveRightMult = %f"), driveLeftMult, driveRightMult);
	UE_LOG(LogTemp, Warning, TEXT("deltaPos = %f, deltaRot = %f"), deltaPos, deltaRot);
	
	UE_LOG(LogTemp, Warning, TEXT("actorLoc = <%f, %f, %f>, forwardVec = <%f, %f, %f>"),
		self->GetActorLocation().X, self->GetActorLocation().Y, self->GetActorLocation().Z,
		self->GetActorRotation().Pitch, self->GetActorRotation().Yaw, self->GetActorRotation().Roll);
}