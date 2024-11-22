// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pin.generated.h"


UENUM()
enum class PinType { MALE, FEMALE, FORK };

UCLASS(Abstract, ClassGroup=(Custom), meta = (BlueprintSpawnableComponent))
class TRUDEMO_API APin : public AActor {
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	APin();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure)
	bool isTaken() const { return taken; }

	UFUNCTION(BlueprintCallable)
	void setTaken(bool newStatus) { taken = newStatus; }

	UFUNCTION(BlueprintPure)
	virtual bool requiresScrew() {
		PURE_VIRTUAL(APin::requiresScrew, );

		// happy compiler
		return false;
	}

	UFUNCTION(BlueprintPure)
	virtual PinType getType() {
		PURE_VIRTUAL(APin::getType, );
		
		// happy compiler
		return PinType::MALE;
	}

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	bool taken;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* pinMesh = nullptr;
};

// Pin that accepts male wires
UCLASS(ClassGroup = (Custom), meta=(BlueprintSpawnableComponent))
class TRUDEMO_API AMalePin : public APin {
	GENERATED_BODY()

public:
	AMalePin();

	virtual bool requiresScrew() override { return false; }
	virtual PinType getType() override { return PinType::MALE; }
};

// Pin that accepts male wires and requires screwing in
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TRUDEMO_API AMalePinScrew : public APin {
	GENERATED_BODY()

public:
	virtual bool requiresScrew() override { return true; }
	virtual PinType getType() override { return PinType::MALE; }
};

// Pin that accepts female wires
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TRUDEMO_API AFemalePin : public APin {
	GENERATED_BODY()

public:
	virtual bool requiresScrew() override { return false; }
	virtual PinType getType() override { return PinType::FEMALE; }
};

// Pin that accepts fork wires
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TRUDEMO_API AForkPin : public APin {
	GENERATED_BODY()

public:
	virtual bool requiresScrew() override { return true; }
	virtual PinType getType() override { return PinType::FORK; }
};
