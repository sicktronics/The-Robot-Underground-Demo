// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
/* For including third-party libraries*/
THIRD_PARTY_INCLUDES_START
#include "../../ThirdParty/Win64LEDBlinkTest1/src/glueCode/index.h"
THIRD_PARTY_INCLUDES_END

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
/* 
* Class that interfaces with the simulation library.
* Using inline static functions because getting errors with stashing implementations in .CPP. 
*/
class FLEDBlinkTestModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/* Get access to module's interface */
	static inline FLEDBlinkTestModule& Get() {
		return FModuleManager::LoadModuleChecked<FLEDBlinkTestModule>("LEDBlinkTest");
	}

	/* Checks to see if module is loaded and ready */
	static inline bool IsAvailable() {
		return FModuleManager::Get().IsModuleLoaded("LEDBlinkTest");
	}
	/* Compile and run the LED Blink test simulation*/
	static inline void compileAndRunLEDBlinkTest(){
		UE_LOG(LogTemp, Warning, TEXT("Inside compileAndRunLEDBlinkTest!!"));
		compileAndRun();
	}
	/* Return the state of LED 13*/
	static inline bool getLED13(){
		return led13;
	}
	/* Check if the simulation is actively running */
	static inline bool isSimulationTicking(){
		if(runner != nullptr && simBeginTicking == true) {
			return true;
		}
		return false;
	}
	/* Stop the simulation from looping*/
	static inline void stopSimInternal(){
		simBeginTicking = false;
	}
};
