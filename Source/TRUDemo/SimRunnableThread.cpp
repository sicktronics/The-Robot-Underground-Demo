// #include "LEDBlinkTest.h"
#include "SimRunnableThread.h"

FSimRunnableThread::FSimRunnableThread()
{
	Thread = FRunnableThread::Create(this, TEXT("Sim Thread"));
}

bool FSimRunnableThread::Init(){
	UE_LOG(LogTemp, Log, TEXT("Thread, begin!")); 

	return true;
}

uint32 FSimRunnableThread::Run()
{

	// Old and gross
	// UE::Tasks::Launch(
	// 	UE_SOURCE_LOCATION,
	// 	[]{ 
	// 		// UE_LOG(LogTemp, Log, TEXT("Hello Tasks!")); 
	// 		if(FLEDBlinkTestModule::IsAvailable()){
	// 			UE_LOG(LogTemp, Warning, TEXT("LEDBlinkTestModule is available!"));
	// 			FLEDBlinkTestModule::compileAndRunLEDBlinkTest();
	// 		}
	// 	});
	UE_LOG(LogTemp, Warning, TEXT("Running the sim..."));
	if(FLEDBlinkTestModule::IsAvailable()){
		UE_LOG(LogTemp, Warning, TEXT("LEDBlinkTestModule is available!"));
		FLEDBlinkTestModule::compileAndRunLEDBlinkTest();
	}

	// Return success
	return 0;
}


void FSimRunnableThread::Exit()
{
	UE_LOG(LogTemp, Warning, TEXT("Killing the sim"));
	// Here's where we can do any cleanup we want to 
	// FLEDBlinkTestModule::stopSimInternal();
}


void FSimRunnableThread::Stop()
{
	// Force our thread to stop early
	// bShutdown = true;
	UE_LOG(LogTemp, Warning, TEXT("Sim ended"));
	FLEDBlinkTestModule::stopSimInternal();

}