// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "SimExecute.h"
#include "LED13Actor.h"
#include "SimRunnableThread.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "LEDBlinkTest1GameModeBase.generated.h"

/**
 * Game mode for the LED Blink test!
 */
UCLASS()
class TRUDEMO_API ALEDBlinkTest1GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	protected:

	// Called when the game starts
	virtual void BeginPlay() override;
	
};
