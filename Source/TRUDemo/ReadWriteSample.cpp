// Fill out your copyright notice in the Description page of Project Settings.


#include "ReadWriteSample.h"

#include "HAL/PlatformFileManager.h"
#include "Misc/FileHelper.h"

FString UReadWriteSample::ReadFromFile(FString filepath, FString& info) {
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*filepath)) {

		return	"File does not exist";
	}
	FString reading = "";
	if (!FFileHelper::LoadFileToString(reading, *filepath)) {

		return "Load file failed";
	}
	info = FString::Printf(TEXT("Read Done"), *filepath);

	return reading;
}

void UReadWriteSample::WriteToFile(FString filepath, FString content, FString& info) {
    FString input = "Orginal Input\n";
    input += content;
	TArray<FString> Commands = ParseString(content);
    TArray<FString> packageResult, signalResult;
	FunctionSelector(Commands, packageResult, signalResult);
    packageResult.Append(signalResult);
    FString dPath = FPaths::ProjectDir() + TEXT("package.txt");
    for (const FString& Line : packageResult) {
        input += Line + LINE_TERMINATOR;
    }

	if (FFileHelper::SaveStringToFile(input, *dPath)) {
        info = FString::Printf(TEXT("Write to %s Done"), *dPath);
	}
    else {
        info = FString::Printf(TEXT("Failed to write to %s"), *dPath);
        return;
    }
    input = "";
    for (const FString& Line : signalResult) {
        input += Line + LINE_TERMINATOR;
    }
    dPath = FPaths::ProjectDir() + TEXT("signal.txt");
    if (FFileHelper::SaveStringToFile(input, *dPath)) {
        info = FString::Printf(TEXT("Write to %s Done"), *dPath);
      
    }
    else {
        info = FString::Printf(TEXT("Failed to write to %s"), *dPath);
        return;
    }
}

TArray<FString> UReadWriteSample::ParseString(const FString& Input) {
	TArray<FString> Commands, RawCommands;
	FString TrimmedCommand;
	Input.ParseIntoArray(RawCommands, TEXT(";"), true);

	for (FString& Command : RawCommands) {
		Command.TrimStartAndEndInline();
		if (!Command.IsEmpty()) {
			Commands.Add(Command);
		}
	}
	return Commands;
}

void UReadWriteSample::FunctionSelector(const TArray<FString>& Commands, TArray<FString>& packageResult, TArray<FString>& signalResult) {
	TArray<FString> packageBits, signalBits;
    packageBits.SetNum(Pins);
    signalBits.SetNum(Pins);
    int32 TickPerSec = 1000 / Tick;
    TArray<int32> pinStatus;
    pinStatus.Init(0, Pins);
    int32 TickCount = 0 , Time = 0, Speed = 0;

    for (const FString& Command : Commands) {
        if (Time < MaxTimeframe){
        int32 OpenParenIndex, CloseParenIndex;
        if (Command.FindChar('(', OpenParenIndex) && Command.FindChar(')', CloseParenIndex)) {
            // Extract the function name and the parameters inside parentheses
            FString FunctionName = Command.Left(OpenParenIndex);
            FString ParametersString = Command.Mid(OpenParenIndex + 1, CloseParenIndex - OpenParenIndex - 1);

            // Split the parameters by comma
            TArray<FString> ParametersArray;
            ParametersString.ParseIntoArray(ParametersArray, TEXT(","), true);
            if (FunctionName.Equals("analogWrite", ESearchCase::IgnoreCase)) {
                int32 IntParameter = FCString::Atoi(*ParametersArray[0].TrimStartAndEnd());
                Speed = IntParameter;

            }
            if (FunctionName.Equals("digitalWrite", ESearchCase::IgnoreCase)) {
                int32 IntParameter = FCString::Atoi(*ParametersArray[0].TrimStartAndEnd());
                FString StringParameter = ParametersArray[1].TrimStartAndEnd();
                if (StringParameter.StartsWith("\"") && StringParameter.EndsWith("\"")) {
                    StringParameter = StringParameter.Mid(1, StringParameter.Len() - 2);
                }
                UE_LOG(LogTemp,Log, TEXT("digitalWrite detected pin: %d , %s"), IntParameter , *StringParameter);
                switch (IntParameter) {
                case 1:
                    if (StringParameter.Equals("HIGH", ESearchCase::IgnoreCase)) {
                        pinStatus[0] = 1;
                    }
                    else {
                        pinStatus[0] = 0;
                    }
                    break;
                case 2:
                    if (StringParameter.Equals("HIGH", ESearchCase::IgnoreCase)) {
                        pinStatus[1] = 1;
                    }
                    else {
                        pinStatus[1] = 0;
                    }
                    break;
                case 3:
                    if (StringParameter.Equals("HIGH", ESearchCase::IgnoreCase)) {
                        pinStatus[2] = 1;
                    }
                    else {
                        pinStatus[2] = 0;
                    }
                    break;
                case 4:
                    if (StringParameter.Equals("HIGH", ESearchCase::IgnoreCase)) {
                        pinStatus[3] = 1;
                    }
                    else {
                        pinStatus[3] = 0;
                    }
                    break;
                default:
                    break;
                }
            }

            if (FunctionName.Equals("delay", ESearchCase::IgnoreCase)) {
                int32 IntParameter = FCString::Atoi(*ParametersArray[0].TrimStartAndEnd());
                while (IntParameter > 0) {
                    for (int i = 0; i < Pins; i++) {
                        packageBits[i] += FString::FromInt(pinStatus[i]);
                    }
                    for (int i = 0; i < Pins; i++) {
                        for (int j = 0; j < MaxSpeed; j++) {
                            if (j < Speed) {
                                signalBits[i] += FString::FromInt(pinStatus[i]);
                            }
                            else {
                                signalBits[i] += FString::FromInt(0);
                            }
                        }                      
                    }
                    TickCount += 1;
                    if (TickCount >= TickPerSec) {
                        ProgressTick(packageResult, packageBits,Time, TickCount,pinStatus, signalResult, signalBits, Speed);
                        }
                    IntParameter = IntParameter - Tick;
                    }
                }           

            }

        }
    }
    //Finish whatever left
    while (Time < MaxTimeframe) {
        ProgressTick(packageResult, packageBits,Time,TickCount, pinStatus, signalResult, signalBits, Speed);
    }
}

void UReadWriteSample::ProgressTick(TArray<FString>& Package, TArray<FString>& PackageBits, int32& Time, int32& TickCount,TArray<int32>& PinStatus , 
    TArray<FString>& Signal, TArray<FString>& SignalBits , int32& Speed) {
    if (Time==0) {//header
        Package.Add(FString("\nPackage output"));
        Package.Add(FString("Time frame total = ") + FString::FromInt(MaxTimeframe) + FString(", ms per tick = ")
            + FString::FromInt(Tick) + FString("ms"));
        Signal.Add(FString("Signal output"));
    }
    while (TickCount < (1000 / Tick)) {  //pad the rest of tick in the time frame
        for (int i = 0; i < Pins; i++) {
            PackageBits[i] += FString::FromInt(PinStatus[i]);
        }
        for (int i = 0; i < Pins; i++) {
            for (int j = 0; j < MaxSpeed; j++) {
                if (j < Speed) {
                    SignalBits[i] += FString::FromInt(PinStatus[i]);
                }
                else {
                    SignalBits[i] += FString::FromInt(0);
                }
            }
        }
        TickCount += 1;
    }
    //Now write to array
    Package.Add(FString("**********"));
    Package.Add(FString("t = ") + FString::FromInt(Time));
    for (int i = 0; i < Pins; i++) {
        Package.Add(FString("pin") + FString::FromInt(i+1) + FString(" : ") + PackageBits[i]);
        PackageBits[i] = "";
    }
    Signal.Add(FString("**********"));
    Signal.Add(FString("t = ") + FString::FromInt(Time));
    for (int i = 0; i < Pins; i++) {
        Signal.Add(FString("pin") + FString::FromInt(i + 1) + FString(" : ") + SignalBits[i]);
        SignalBits[i] = "";
    }
    Time += 1;
    TickCount = 0;
}