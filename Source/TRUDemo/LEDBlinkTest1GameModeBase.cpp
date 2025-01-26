// Fill out your copyright notice in the Description page of Project Settings.


#include "LEDBlinkTest1GameModeBase.h"

// Called when the game starts
void ALEDBlinkTest1GameModeBase::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Let the games begin"));

    // Spawn SimIndex and get reference
    // ASimIndex* MySimIndex = (ASimIndex*) GetWorld()->SpawnActor(ASimIndex::StaticClass());

    // Spawn SimExecute
    // ASimExecute* MySimExecute = (ASimExecute*) GetWorld()->SpawnActor(ASimExecute::StaticClass());

    // Spawn LED 13
    // ALED13Actor* MyLED13Actor = (ALED13Actor*) GetWorld()->SpawnActor(ALED13Actor::StaticClass());

    // Give a reference of LED 13 to MySimExecute!!
    // MySimExecute->ReceiveLED13Actor(MyLED13Actor);

    // And then MySimExecute will call the function in LED13 class

}