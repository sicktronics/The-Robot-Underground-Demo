// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Wireable.h"
#include "Wire.h"

#include "WiringManager.generated.h"


/*
 * Enum holding the current wiring state. States:
 *
 * NONE - nothing is currently selected
 * WIRE_SELECTED - a wire has been selected, no pins yet
 * PIN1_DONE	the first pin has been completed (already
 *		screwed in if necessary)
 * PIN1_SCREW - the first pin has been selected but needs
 *		to be screwed in
 * PIN2_SCREW - the second pin has been selected but needs
 *		to be screwed in
 *
 * NOTE: There isn't a PIN2_DONE since if it's done, it
 * should just go to NONE since there's nothing left
 * for the player to do... unless animations???
 */
UENUM()
enum class WiringState : uint8 {
	NONE			UMETA(DisplayName = "NONE"),
	WIRE_SELECTED	UMETA(DisplayName = "WIRE_SELECTED"),
	PIN1_DONE		UMETA(DisplayName = "PIN1_DONE"),
	PIN1_SCREW		UMETA(DisplayName = "PIN1_SCREW"),
	PIN2_SCREW		UMETA(DisplayName = "PIN2_SCREW")
};

/**
 * Manages the wiring state and stuff. Should really only have one instance in the world at a time.
 */
UCLASS()
class TRUDEMO_API AWiringManager : public AActor {
	GENERATED_BODY()

public:
	AWiringManager();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
protected:
	UPROPERTY(VisibleAnywhere)
	WiringState currState;

	UPROPERTY(VisibleAnywhere)
	TArray<AWireable*> wireables;

	UPROPERTY(VisibleAnywhere)
	AWire* currWire;

	// Called when the game starts
	virtual void BeginPlay() override;
};
