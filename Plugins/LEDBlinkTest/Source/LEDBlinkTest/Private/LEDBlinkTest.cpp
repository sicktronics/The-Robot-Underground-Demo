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

#undef LOCTEXT_NAMESPACE
	
