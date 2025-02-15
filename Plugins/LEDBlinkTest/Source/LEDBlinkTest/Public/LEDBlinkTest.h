// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

THIRD_PARTY_INCLUDES_START
#include "../../ThirdParty/Win64LEDBlinkTest1/src/glueCode/index.h"
THIRD_PARTY_INCLUDES_END

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

class FLEDBlinkTestModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	// /* Get access to module's interface */
	static inline FLEDBlinkTestModule& Get() {
		return FModuleManager::LoadModuleChecked<FLEDBlinkTestModule>("LEDBlinkTest");
	}

	// /* Checks to see if module is loaded and ready */
	static inline bool IsAvailable() {
		return FModuleManager::Get().IsModuleLoaded("LEDBlinkTest");
	}

	static inline void compileAndRunLEDBlinkTest(){
		UE_LOG(LogTemp, Warning, TEXT("Inside compileAndRunLEDBlinkTest!!"));
		compileAndRun();
	}

	static inline bool getLED13(){
		return led13;
	}

	static inline bool isSimulationTicking(){
		if(runner != nullptr && simBeginTicking == true) {
			return true;
		}
		return false;
	}
	static inline void stopSimInternal(){
		simBeginTicking = false;
		// runner->~AVRRunner();
	}

	// UFUNCTION()
	// bool getLED13();

	// UFUNCTION()
	// void compileAndRunLEDBlinkTest();

	// /* Checking whether the simulation is active or not */
	// UFUNCTION()
	// bool isSimulationTicking();
};
