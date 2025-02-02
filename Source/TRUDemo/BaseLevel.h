// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseLevel.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRUDEMO_API UBaseLevel : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseLevel();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ALevelLoader* levelLoader;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// *******************
	// Here we can put any functionality that we want to be true for all levels
	// stuff like tracking level progress and such 
	UFUNCTION(BlueprintCallable)
	void SetLevelLoader(ALevelLoader* l);
	UFUNCTION(BlueprintCallable)
	ALevelLoader* GetLevelLoader();
};
