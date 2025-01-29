// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Functions.h"
#include "BaseLevel.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LevelLoader.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRUDEMO_API ULevelLoader : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULevelLoader();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core")
	TSubclassOf<class AActor>  MyClassType;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	TSubclassOf<class AActor> GetLevel();
	UFUNCTION(BlueprintCallable)
	UBaseLevel* GetBaseLevelComponent(AActor* obj);	
};
