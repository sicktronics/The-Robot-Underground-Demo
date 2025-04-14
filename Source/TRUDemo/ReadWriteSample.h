// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ReadWriteSample.generated.h"

constexpr int32 MaxTimeframe = 10;
constexpr int32 MaxSpeed = 255;
constexpr int32	Tick = 1; //This is ms per tick
constexpr int32 Pins = 8;


/**
 * 
 */
UCLASS()
class TRUDEMO_API UReadWriteSample : public UBlueprintFunctionLibrary
{
	
	UFUNCTION(BlueprintCallable)
		static FString ReadFromFile(FString filepath, FString& info);

	UFUNCTION(BlueprintCallable)
		static FString WriteToFile(FString filepath, FString Content);
		static void ProgressTick(TArray<FString>& Package, TArray<FString>& PackageBits, int32& Time, 
			int32& TickCount, TArray<int32>& PinStatus, TArray<FString>& Signal, TArray<FString>& SignalBits, 
			TArray<int32>& PinSpeed, TArray<int32>& PinActive);

		static bool IsNumeric(const FString& String);

		static TArray<FString> cleanInput(const FString& Input);

		static void PrintStringArray(const TArray<FString>& StringArray);

		static void PrintFunctionDict(const TMap<FString, TArray<FString>>& FunctionDict);

		static void PrintVarArray(const TArray<TArray<FString>>& VarArray);

		static void PinMode(const TArray<FString>& Para, TArray<int32>& pinActive, TArray<TArray<FString>>& VarStack);

		static void AnalogWrite(const TArray<FString>& Para, TArray<int32>& pinSpeed, TArray<TArray<FString>>& VarStack);

		static void DigitalWrite(const TArray<FString>& Para, TArray<int32>& pinStatus, TArray<TArray<FString>>& VarStack);

		static void Delay(const TArray<FString>& Para, TArray<FString>& Package, TArray<FString>& PackageBits, 
			int32& Time, int32& TickCount, TArray<int32>& PinStatus,
			TArray<FString>& Signal, TArray<FString>& SignalBits, TArray<int32>& PinSpeed, 
			TArray<int32>& PinActive, TArray<TArray<FString>>& VarStack);

		static void ParseFunction(const TArray<FString>& Command, TMap<FString, TArray<FString>>& FunctionDict, 
			TArray<TArray<FString>>& VarStack);
		
		static void PushVar(const FString& Command, TArray<TArray<FString>>& VarStack);

		static void PopVar(int& VarCount, TArray<TArray<FString>>& VarStack);

		static void CallFunction(const FString& FunctionNameIn, TMap<FString, TArray<FString>>& FunctionDict,
			TArray<TArray<FString>>& VarStack, TArray<FString>& Package, TArray<FString>& PackageBits,
			int32& Time, int32& TickCount, TArray<int32>& PinStatus,TArray<FString>& Signal, 
			TArray<FString>& SignalBits, TArray<int32>& PinSpeed, TArray<int32>& PinActive, FString& compileMessage);

		static FString GetVar(const FString& VarName, TArray<TArray<FString>>& VarStack);

	GENERATED_BODY()
	
};
