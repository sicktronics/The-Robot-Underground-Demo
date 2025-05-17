// #include "LEDBlinkTest.h"
#include "SimRunnableThread.h"
/*
* Creates the thread, Create() internally calls Init()
*/
FSimRunnableThread::FSimRunnableThread()
{
	Thread = FRunnableThread::Create(this, TEXT("Sim Thread"));
}

/*
* Logic for determining successful initialization
*/
bool FSimRunnableThread::Init(){
	UE_LOG(LogTemp, Log, TEXT("Thread, begin!")); 

	return true;
}
/*
* If initialization returns true, Run() is called
*/
uint32 FSimRunnableThread::Run()
{
	// If the LED Blink Test plugin module is loaded, kick off the simulation!
	if(FLEDBlinkTestModule::IsAvailable()){
		// UE_LOG(LogTemp, Warning, TEXT("LEDBlinkTestModule is available!"));
		FLEDBlinkTestModule::compileAndRunLEDBlinkTest();
	}

	// Return success
	return 0;
}

/*
* Cleanup, etc
*/
void FSimRunnableThread::Exit()
{
	UE_LOG(LogTemp, Warning, TEXT("Killing the sim"));
	// Here's where we can do any cleanup we want to
}

/*
* This runs when we call Thread->Kill()--proper way to end the thread when we're
* done with the simulation
*/
void FSimRunnableThread::Stop()
{
	// Force our thread to stop early
	// bShutdown = true;
	UE_LOG(LogTemp, Warning, TEXT("Sim ended"));
	// Stop simulation internally
	FLEDBlinkTestModule::stopSimInternal();
	// reset thread pointer
	Thread = nullptr;

}