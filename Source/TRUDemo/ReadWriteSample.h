// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ReadWriteSample.generated.h"

constexpr int32 MaxTimeframe = 5;
constexpr int32 MaxSpeed = 255;
constexpr int32	Tick = 1; //This is ms per tick
constexpr int32 Pins = 4;


/**
 * 
 */
UCLASS()
class TRUDEMO_API UReadWriteSample : public UBlueprintFunctionLibrary
{
	
	UFUNCTION(BlueprintCallable)
		static FString ReadFromFile(FString filepath, FString& OutInfo);

	UFUNCTION(BlueprintCallable)
		static void WriteToFile(FString filepath, FString Content,FString& OutInfo);

	UFUNCTION(BlueprintCallable)
		static TArray<FString> ParseString(const FString& Input);

	UFUNCTION(BlueprintCallable)
		static void FunctionSelector(const TArray<FString>& Commands, TArray<FString>& packageResult, TArray<FString>& signalResult);
	UFUNCTION(BlueprintCallable)
		static void ProgressTick(TArray<FString>& Result, TArray<FString>& Package,int32& Time, int32& TickCount,TArray<int32>& PinStatus,
			TArray<FString>& Signal, TArray<FString>& SignalBits, int32& Speed);

	GENERATED_BODY()
	
};
