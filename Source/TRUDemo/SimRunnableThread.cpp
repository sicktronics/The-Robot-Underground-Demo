#include "LEDBlinkTest.h"
#include "SimRunnableThread.h"

FSimRunnableThread::FSimRunnableThread(int32 InTargetCount)
{
	TargetCount = InTargetCount;
	FoundCount = 0;
	Thread = FRunnableThread::Create(this, TEXT("This is my thread example"));
}

FSimRunnableThread::~FSimRunnableThread()
{
	if (Thread != nullptr)
	{
		Thread->Kill(true);
		delete Thread;
	}
}

uint32 FSimRunnableThread::Run()
{
	// bStopThread = false;
	// if(!bStopThread){
    // // if(!bStopThread && FLEDBlinkTestModule::IsAvailable()){
    //     UE_LOG(LogTemp, Warning, TEXT("Fired on a different thread!"));
	// 	compileAndRun();
    //     // FLEDBlinkTestModule::Get();
    //     // FLEDBlinkTestModule::compileAndRunLEDBlinkTest();
    //     // if(FLEDBlinkTestModule::Get()){
    //     // 	UE_LOG(LogTemp, Warning, TEXT("Got a reference!"));
    //     // }
    // }

	// Keep processing until we're cancelled through Stop() or we're done,
	// although this thread will suspended for other stuff to happen at the same time
	// while (!bStopThread && FoundCount < TargetCount)
	// {
		// This is where we would do our expensive threaded processing


		// Instead we're going to make a really busy while loop to slow down processing
		// You can change INT_MAX to something smaller if you want it to run faster
		// int32 x = 0;
		// while (x < INT_MAX)
		// {
		// 	x++;
		// }
		// ProcessedNumbers.Add(FMath::RandRange(0, 999));
		// FoundCount += 1;
	// }

	// OnCompleteDelegate.ExecuteIfBound();

	// Return success
	return 0;
}


void FSimRunnableThread::Exit()
{
	// Here's where we can do any cleanup we want to 
}


void FSimRunnableThread::Stop()
{
	// Force our thread to stop early
	bStopThread = true;
}