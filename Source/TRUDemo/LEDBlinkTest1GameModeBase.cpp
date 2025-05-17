// Fill out your copyright notice in the Description page of Project Settings.


#include "LEDBlinkTest1GameModeBase.h"

// Called when the game starts
void ALEDBlinkTest1GameModeBase::BeginPlay()
{   

	Super::BeginPlay();
    
	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Let the games begin"));

    // Turning off lighting to give my poor little laptop a break
    UGameViewportClient* GameViewport =  GetWorld()->GetGameViewport();
	GameViewport->ViewModeIndex = 2;

}