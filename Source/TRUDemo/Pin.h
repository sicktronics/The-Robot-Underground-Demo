// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Pin.generated.h"


UENUM()
enum class PinType { MALE, FEMALE, MALE_SCREW, FORK };

UCLASS(Abstract, ClassGroup=(Custom), meta = (BlueprintSpawnableComponent))
class TRUDEMO_API UPin : public UActorComponent {
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPin();

	UFUNCTION(BlueprintPure)
	bool isTaken() const { return taken; }

	UFUNCTION(BlueprintCallable)
	void setTaken(bool newStatus) { taken = newStatus; }

	UFUNCTION(BlueprintPure)
	virtual bool requiresScrew() {
		PURE_VIRTUAL(UPin::requiresScrew, );

		// happy compiler
		return false;
	}

	UFUNCTION(BlueprintPure)
	virtual PinType getType() {
		PURE_VIRTUAL(UPin::getType, );
		
		// happy compiler
		return PinType::MALE;
	}

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	bool taken;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

// Pin that accepts male wires
UCLASS(ClassGroup = (Custom), meta=(BlueprintSpawnableComponent))
class TRUDEMO_API UMalePin : public UPin {
	GENERATED_BODY()

public:
	virtual bool requiresScrew() override { return false; }
	virtual PinType getType() override { return PinType::MALE; }
};
