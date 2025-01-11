// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CameraPosition.h"
#include "Functions.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CameraMover.generated.h"




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRUDEMO_API UCameraMover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCameraMover();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core")
	AActor* self;
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
	// int playState = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Values")
	AActor* currentPos = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
	AActor* startPos = nullptr;
	
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "States")
	// AActor* playerController;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void CycleAdjStateLocation(FString inputKey);
	void MoveToStateLocation(AActor* loc);

	// UFUNCTION(BlueprintCallable)
	// void SetPlayerController(AActor* pc);
		
};
