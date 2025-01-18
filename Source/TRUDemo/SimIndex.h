// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

THIRD_PARTY_INCLUDES_START
#include "../../Plugins/LEDBlinkTest1/Source/ThirdParty/LEDBlinkTest1Library/src/CPU/CPU.h"
#include "../../Plugins/LEDBlinkTest1/Source/ThirdParty/LEDBlinkTest1Library/src/CPU/interrupt.h"
#include "../../Plugins/LEDBlinkTest1/Source/ThirdParty/LEDBlinkTest1Library/src/CPU/instruction.h"
#include "../../Plugins/LEDBlinkTest1/Source/ThirdParty/LEDBlinkTest1Library/src/glueCode/compile.h"
#include "../../Plugins/LEDBlinkTest1/Source/ThirdParty/LEDBlinkTest1Library/src/glueCode/execute.h"
#include "../../Plugins/LEDBlinkTest1/Source/ThirdParty/LEDBlinkTest1Library/src/glueCode/intelHex.h"
#include "../../Plugins/LEDBlinkTest1/Source/ThirdParty/LEDBlinkTest1Library/src/peripherals/GPIO.h"
#include "../../Plugins/LEDBlinkTest1/Source/ThirdParty/LEDBlinkTest1Library/src/peripherals/GPIO.h"
THIRD_PARTY_INCLUDES_END

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimIndex.generated.h"

UCLASS()
class TRUDEMO_API ASimIndex : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASimIndex();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*** Simulation support functions VVV ***/

	UFUNCTION(BlueprintCallable)
	void CompileAndRun();

	UFUNCTION(BlueprintCallable)
	void ExecuteProgram();

};
