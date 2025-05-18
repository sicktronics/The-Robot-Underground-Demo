    // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Functions.h"
#include "Misc/Paths.h"

#include "TempCPU.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRUDEMO_API UTempCPU : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTempCPU();

	//UPROPERTY(EditAnywhere, Category = "Core")
	FString retString;

	UPROPERTY(EditAnywhere, Category = "Core")
	FString filename = "signal.txt";

	// The path to the /Content folder, where signal files live
	UPROPERTY(EditAnywhere, Category = "Core")
	FString pathToFile = "Content/TextFile/";

	//UPROPERTY(EditAnywhere, Category = "Runtime Connection List")
	TArray<FString> pins;

	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void LoadPinData();	
	void SplitPinData();
	int GetPinData(int pinNum, int loc);

	bool IsValidTick(int tick);
};
