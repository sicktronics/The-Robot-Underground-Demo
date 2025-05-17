#pragma once

#include "LEDBlinkTest.h"
#include "LED13Actor.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "GenericPlatform/GenericPlatformProcess.h"
#include "HAL/Runnable.h"

/*
* Class for giving the simualtion a dedicated thread.
* Note that we do not have to mark our class as UCLASS() if we don't want to
*/
class FSimRunnableThread : public FRunnable
{
public:
	// Custom constructor for setting up our thread with its target
	FSimRunnableThread();

	// FRunnable functions
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;
	// Pointer to the thread, boolean for shutting down (not used)
	FRunnableThread* Thread = nullptr;
	bool bShutdown = false;
};