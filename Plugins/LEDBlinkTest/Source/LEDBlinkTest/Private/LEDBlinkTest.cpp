// Copyright Epic Games, Inc. All Rights Reserved.

#include "LEDBlinkTest.h"



#define LOCTEXT_NAMESPACE "FLEDBlinkTestModule"

IMPLEMENT_MODULE(FLEDBlinkTestModule, LEDBlinkTest)

void FLEDBlinkTestModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FLEDBlinkTestModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}
// Returning the value of LED 13 on the board
// bool FLEDBlinkTestModule::getLED13() {
// 	if (led13){
// 		return true;
// 	}
// 	return false;
// 	// return true;
// }

// void FLEDBlinkTestModule::compileAndRunLEDBlinkTest() {
// 	compileAndRun();
// 	// UE_LOG(LogTemp, Warning, TEXT("Inside compileAndRunLEDBlinkTest!!"));
// }

// bool FLEDBlinkTestModule::isSimulationTicking() {
// 	if(runner != nullptr && simBeginTicking == true) {
// 		return true;
// 	}
// 	return false;
// }

#undef LOCTEXT_NAMESPACE
	
