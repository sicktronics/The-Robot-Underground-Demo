// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TempCPU.h"
#include "Functions.h"


#include "Robot.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRUDEMO_API URobot : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URobot();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core Data")
	float moveSpeed;
	UPROPERTY(EditAnywhere, Category = "Core Data")
	float robotWidth = 1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Pin Numbers")
	int driveLeftPin = 1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Pin Numbers")
	int driveRightPin = 2;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Pin Numbers")
	int leftBackwardPin = 3;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Pin Numbers")
	int leftForwardPin = 4;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Pin Numbers")
	int rightBackwardPin = 5;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Pin Numbers")
	int rightForwardPin = 6;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Pin Numbers")
	int clawOne = 7;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Pin Numbers")
	int clawTwo = 8;
	UPROPERTY(VisibleAnywhere, Category = "Moter Speeds")
	float driveLeftMult;
	UPROPERTY(VisibleAnywhere, Category = "Moter Speeds")
	float driveRightMult;
	UPROPERTY(VisibleAnywhere, Category = "Derived Data")
	AActor* self;
	UPROPERTY(VisibleAnywhere, Category = "Derived Data")
	int tick = 0;
	UPROPERTY(VisibleAnywhere, Category = "Derived Data")
	bool go = false;
	UPROPERTY(VisibleAnywhere, Category = "Derived Data")
	FRotator initRotation;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	FRotator GetMovementVector(float DeltaTime);
	UFUNCTION(BlueprintCallable)
	float ToSpeedDCMotor(int input, float avg);
	UFUNCTION(BlueprintCallable)
	float GetDriveSpeed(float DeltaTime);
	UFUNCTION(BlueprintCallable)
	void SetGo();
};