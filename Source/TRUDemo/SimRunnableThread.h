#pragma once

#include "LEDBlinkTest.h"
#include "HAL/Runnable.h"


// Note that we do not have to mark our class as UCLASS() if we don't want to
class FSimRunnableThread : public FRunnable
{
public:
	// Custom constructor for setting up our thread with its target
	FSimRunnableThread(int32 InTargetCount);
	virtual ~FSimRunnableThread();

	// FRunnable functions
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;
	// FRunnable

	// FBUIOnCompleteSignature OnCompleteDelegate;

protected:
	FRunnableThread* Thread = nullptr;

	TArray<int32> ProcessedNumbers;

	int32 TargetCount = -1;
	int32 FoundCount = -1;

	bool bStopThread = false;
};