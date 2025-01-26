// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "SimIndex.h"
#include "SimExecute.h"
#include "LED13Actor.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LEDBlinkTest1GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TRUDEMO_API ALEDBlinkTest1GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	protected:

	// Called when the game starts
	virtual void BeginPlay() override;
	
};
