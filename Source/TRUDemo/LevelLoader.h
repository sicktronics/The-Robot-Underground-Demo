// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Functions.h"
#include "BaseLevel.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelLoader.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRUDEMO_API ALevelLoader : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ALevelLoader();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core")
	TSubclassOf<class AActor>  Level;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	TSubclassOf<class AActor> GetLevelToLoad();
	UFUNCTION(BlueprintCallable)
	UBaseLevel* GetBaseLevelComponent(AActor* obj);	



	
};
