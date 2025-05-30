// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ReadWriteSample.generated.h"

constexpr int32 MaxTimeframe = 120;
constexpr int32 MaxSpeed = 255;
constexpr int32	Tick = 1; //This is ms per tick
constexpr int32 Pins = 19;


/**
 * 
 */
UCLASS()
class TRUDEMO_API UReadWriteSample : public UBlueprintFunctionLibrary
{
	
	UFUNCTION(BlueprintCallable)
		static FString ReadUserInput(int option, int page);

	UFUNCTION(BlueprintCallable)

		static FString SaveUserInput(FString content, int option, int page);

	UFUNCTION(BlueprintCallable)
		static FString WriteToFile(FString Content);
	UFUNCTION(BlueprintCallable)

		static TArray<FString>LoadSaveHeader(int head, int page);


		static void ProgressTick(int32& Time, int32& TickCount, TArray<int32>& PinStatus, 
			TArray<FString>& Signal, TArray<FString>& SignalBits, 
			TArray<int32>& PinSpeed, TArray<int32>& PinActive);

		static bool IsNumeric(const FString& String);

		static bool IsMath(const FString& String);

		static int32 AutoIndex();

		static TArray<FString> cleanInput(const FString& Input);

		static void PrintStringArray(const TArray<FString>& StringArray);

		static void PrintFunctionDict(const TMap<FString, TArray<FString>>& FunctionDict);

		static void PrintVarArray(const TArray<TArray<FString>>& VarArray);

		static void PinMode(TArray<FString>& Para, TArray<int32>& pinActive, TArray<TArray<FString>>& VarStack, TArray<int32>& VarScope, int32& CurrentScope, FString& compileMessage);

		static void AnalogWrite(TArray<FString>& Para, TArray<int32>& pinSpeed, TArray<TArray<FString>>& VarStack, TArray<int32>& VarScope, int32& CurrentScope,TArray<int32>& pinStatus, FString& compileMessage);

		static void DigitalWrite(TArray<FString>& Para, TArray<int32>& pinStatus, TArray<TArray<FString>>& VarStack, TArray<int32>& VarScope, int32& CurrentScope, TArray<int32>& pinSpeed, FString& compileMessage);

		static void Delay(TArray<FString>& Para, int32& Time, int32& TickCount, 
			TArray<int32>& PinStatus,TArray<FString>& Signal, TArray<FString>& SignalBits, TArray<int32>& PinSpeed, 
			TArray<int32>& PinActive, TArray<TArray<FString>>& VarStack, TArray<int32>& VarScope, int32& CurrentScope, FString& compileMessage);

		static void ParseFunction(const TArray<FString>& Command, TMap<FString, TArray<FString>>& FunctionDict, 
			TArray<TArray<FString>>& VarStack, TArray<int32>& VarScope, int32& CurrentScope,FString& compileMessage);
		
		static void PushVar(const FString& Command, TArray<TArray<FString>>& VarStack, TArray<int32>& VarScope, int32& CurrentScope,FString& compileMessage);

		static void PopVar(int& VarCount, TArray<TArray<FString>>& VarStack, TArray<int32>& VarScope);

		static void CallFunction(const FString& FunctionNameIn, TMap<FString, TArray<FString>>& FunctionDict,
			TArray<TArray<FString>>& VarStack, TArray<int32>& VarScope, int32& CurrentScope, int32& Time, int32& TickCount, 
			TArray<int32>& PinStatus,TArray<FString>& Signal,TArray<FString>& SignalBits, 
			TArray<int32>& PinSpeed, TArray<int32>& PinActive, FString& compileMessage);

		static FString GetVar(FString& VarName, TArray<TArray<FString>>& VarStack, TArray<int32>& VarScope, int32& CurrentScope, FString& compileMessage);

		static int32 FindVar(const FString& VarName, TArray<TArray<FString>>& VarStack, TArray<int32>& VarScope, int32& CurrentScope, FString& compileMessage);

		static void ChangeVar(const FString& VarName, const FString& VarVal, TArray<TArray<FString>>& VarStack, TArray<int32>& VarScope, int32& CurrentScope, FString& compileMessage);

		static FString MathOp(FString& VarName, TArray<TArray<FString>>& VarStack, TArray<int32>& VarScope, int32& CurrentScope, FString& compileMessage);

		static TArray<FString> SplitMathOp(const FString& InString);
	GENERATED_BODY()
	
};
