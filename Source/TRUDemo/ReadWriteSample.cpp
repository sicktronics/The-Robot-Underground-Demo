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
    info = FString::Printf(TEXT("Read Done: %s"), *filepath);

    return reading;
}

FString UReadWriteSample::WriteToFile(FString filepath, FString content) {
    FString input = "Orginal Input\n";
    input += content;
    //initalize all variable needed
    TMap<FString, TArray<FString>> FunctionDict;
    TArray<TArray<FString>> VarStack;
    TArray<FString> Commands = cleanInput(content);
    FString complieMessage = "Compile success!";
    //PrintStringArray(Commands);
    ParseFunction(Commands, FunctionDict, VarStack);
    //PrintFunctionDict(FunctionDict);
    //PrintVarArray(VarStack);
    TArray<FString> packageResult, signalResult, packageBits, signalBits;
    packageBits.SetNum(Pins);
    signalBits.SetNum(Pins);
    TArray<int32> pinStatus, pinActive, pinSpeed;
    pinStatus.Init(0, Pins);
    pinActive.Init(0, Pins);
    pinSpeed.Init(0, Pins);
    int32 TickCount = 0, Time = 0;

    //start setup here
    CallFunction(TEXT("setup"), FunctionDict, VarStack, packageResult, packageBits,
        Time, TickCount, pinStatus, signalResult, signalBits, pinSpeed, pinActive, complieMessage);
    input = "";
    for (const FString& Line : signalResult) {
        input += Line + LINE_TERMINATOR;
    }
    FString dPath = FPaths::ProjectDir() + TEXT("signal.txt");
    if (FFileHelper::SaveStringToFile(input, *dPath)) {
        return complieMessage;
    }
    else {
    }
    return complieMessage;
}

void UReadWriteSample::ProgressTick(TArray<FString>& Package, TArray<FString>& PackageBits, int32& Time, int32& TickCount, TArray<int32>& PinStatus,
    TArray<FString>& Signal, TArray<FString>& SignalBits, TArray<int32>& PinSpeed , TArray<int32>& PinActive) {
    if (Time == 0) {//header
        //Package.Add(FString("\nPackage output"));
        //Package.Add(FString("Time frame total = ") + FString::FromInt(MaxTimeframe) + FString(", ms per tick = ")
        //    + FString::FromInt(Tick) + FString("ms"));
        Signal.Add(FString("Signal output"));
    }
    while (TickCount < (1000 / Tick)) {  //pad the rest of tick in the time frame
        //for (int i = 0; i < Pins; i++) {
        //    if (PinActive[i] == 1) {
        //        PackageBits[i] += FString::FromInt(PinStatus[i]);
        //    }
        //    else {
        //        PackageBits[i] += "0";
        //    }
        //}
        for (int i = 0; i < Pins; i++) {
            for (int j = 0; j < MaxSpeed; j++) {
                if (PinActive[i] == 1) {
                    if (j < PinSpeed[i]) {
                        SignalBits[i] += FString::FromInt(PinStatus[i]);
                    }
                    else {
                        SignalBits[i] += FString::FromInt(0);
                    }
                }
                else {
                    SignalBits[i] += "0";
                }

            }
        }
        TickCount += 1;
    }
    //Now write to array
    //Package.Add(FString("**********"));
    //Package.Add(FString("t = ") + FString::FromInt(Time));
    //for (int i = 0; i < Pins; i++) {
    //    Package.Add(FString("pin") + FString::FromInt(i + 1) + FString(" : ") + PackageBits[i]);
    //    PackageBits[i] = "";
    //}
    Signal.Add(FString("**********"));
    Signal.Add(FString("t = ") + FString::FromInt(Time));
    for (int i = 0; i < Pins; i++) {
        Signal.Add(FString("pin") + FString::FromInt(i + 1) + FString(" : ") + SignalBits[i]);
        SignalBits[i] = "";
    }
    Time += 1;
    TickCount = 0;
}

bool UReadWriteSample::IsNumeric(const FString& String)
{
    for (TCHAR Char : String)
    {
        if (!FChar::IsDigit(Char)) // Checks if each character is a digit
        {
            return false;
        }
    }
    return true;
}
 
TArray<FString> UReadWriteSample::cleanInput(const FString& Input) {
    TArray<FString> Commands, RawCommands;
    int32 FirstSlash = INDEX_NONE;
    int32 SecondSlash = INDEX_NONE;
    Input.ParseIntoArray(RawCommands, TEXT("\n"), true);
    for (FString& eachLine : RawCommands) {
        eachLine.TrimStartAndEndInline();
        FString newLine = TEXT("");
        int32 SearchIndex = 0;
        bool doubleDetect = false;
        while (SearchIndex < eachLine.Len()) {
            TCHAR Char = eachLine[SearchIndex];
            if (Char == ';') {
                newLine += Char;
                newLine.TrimStartAndEndInline();
                if (!newLine.IsEmpty()) {
                    Commands.Add(newLine);
                }
                newLine = TEXT("");
                Char = '\0';
            } 
            if (Char == '{') {
                newLine.TrimStartAndEndInline();
                if (!newLine.IsEmpty()) {
                    Commands.Add(newLine);
                }
                newLine = TEXT("{");
                Commands.Add(newLine);
                newLine = TEXT("");
                Char = '\0';
            } 
            if (Char == '}') {
                newLine.TrimStartAndEndInline();
                if (!newLine.IsEmpty()) {
                    Commands.Add(newLine);
                }
                newLine = TEXT("}");
                Commands.Add(newLine);
                newLine = TEXT("");
                Char = '\0';
            }
            if (Char == '/') {
                if (doubleDetect == true) {
                    newLine = newLine.LeftChop(1);
                    newLine.TrimStartAndEndInline();
                    if (!newLine.IsEmpty()) {
                        Commands.Add(newLine);
                    }
                    break;
                }
                else {                    
                    doubleDetect = true;
                }
            }
            else {                
                doubleDetect = false;
            }
            newLine += Char;
            SearchIndex++;
            if (SearchIndex == eachLine.Len()) {
                newLine.TrimStartAndEndInline();
                if (!newLine.IsEmpty()) {
                    Commands.Add(newLine);
                }
               
            }
        }
    }
    return Commands;
}

void UReadWriteSample::PinMode(const TArray<FString>& Para, TArray<int32>& pinActive, TArray<TArray<FString>>& VarStack) {
    if (Para.Num() > 2) {
        return;
    }
    if (!Para[0].IsNumeric()) {
        FString VarValue = GetVar(Para[0], VarStack);
        if (!VarValue.IsEmpty()) {
            pinActive[FCString::Atoi(*VarValue.TrimStartAndEnd()) - 1] = 1;
        }
    }
    if (Para[0].IsNumeric() && Para[1].Equals("OUTPUT", ESearchCase::IgnoreCase)) {
        pinActive[FCString::Atoi(*Para[0].TrimStartAndEnd())-1] = 1;
    }    
}

void UReadWriteSample::AnalogWrite(const TArray<FString>& Para, TArray<int32>& pinSpeed, TArray<TArray<FString>>& VarStack) {
    if (Para.Num() > 2) {
        return;
    }
    FString PinValue, SpeedValue;
    int32 PinNumber, SpeedNumber;
    if (!Para[0].IsNumeric()) {
        PinValue = GetVar(Para[0], VarStack);
        PinNumber = FCString::Atoi(*PinValue.TrimStartAndEnd());
    }
    else {
        PinNumber = FCString::Atoi(*Para[0].TrimStartAndEnd());
    }

    if (!Para[1].IsNumeric()) {
        SpeedValue = GetVar(Para[1], VarStack);
        SpeedNumber = FCString::Atoi(*SpeedValue.TrimStartAndEnd());
    }
    else {
        //UE_LOG(LogTemp, Log, TEXT("Speed numberic"));
        SpeedNumber = FCString::Atoi(*Para[1].TrimStartAndEnd());
    }
    //UE_LOG(LogTemp, Log, TEXT("change speed pin : %d to %d"), PinNumber -1, SpeedNumber);
    if (PinNumber==3 || PinNumber==6) {
        pinSpeed[PinNumber - 2] = SpeedNumber;
        pinSpeed[PinNumber - 3] = SpeedNumber;
    }
    pinSpeed[PinNumber-1] = SpeedNumber;

}

void UReadWriteSample::DigitalWrite(const TArray<FString>& Para, TArray<int32>& pinStatus, TArray<TArray<FString>>& VarStack) {
    if (Para.Num() > 2) {
        return;
    }
    if (!Para[0].IsNumeric()) {
        FString VarValue = GetVar(Para[0],VarStack);
        if (!VarValue.IsEmpty()) {
            if (Para[1].Contains(TEXT("high"), ESearchCase::IgnoreCase)) {
                pinStatus[FCString::Atoi(*VarValue.TrimStartAndEnd()) - 1] = 1;
            }
            else
            if (Para[1].Contains(TEXT("low"), ESearchCase::IgnoreCase)) {
                pinStatus[FCString::Atoi(*VarValue.TrimStartAndEnd()) - 1] = 0;
            }
        }
    }

    if (Para[0].IsNumeric()) {
        if (Para[1].Contains(TEXT("high"), ESearchCase::IgnoreCase)) {
            pinStatus[FCString::Atoi(*Para[0].TrimStartAndEnd()) - 1] = 1;
        }
        else if (Para[1].Contains(TEXT("low"), ESearchCase::IgnoreCase)) {
            pinStatus[FCString::Atoi(*Para[0].TrimStartAndEnd()) - 1] = 0;
        }
        else {
            return;
        }

    }

}

void UReadWriteSample::Delay(const TArray<FString>& Para,TArray<FString>& Package, TArray<FString>& PackageBits, int32& Time, int32& TickCount, TArray<int32>& PinStatus,
    TArray<FString>& Signal, TArray<FString>& SignalBits, TArray<int32>& PinSpeed, TArray<int32>& PinActive, TArray<TArray<FString>>& VarStack) {

    if (Para.Num() > 1) {
        return;
    }
    int32 IntParameter = 0 ;
    if (!Para[0].IsNumeric()) {
        FString VarValue = GetVar(Para[0], VarStack);
        if (!VarValue.IsEmpty()) {
            IntParameter = FCString::Atoi(*VarValue.TrimStartAndEnd());
        }
    }
    else {
        IntParameter = FCString::Atoi(*Para[0].TrimStartAndEnd());
    }

    UE_LOG(LogTemp, Log, TEXT("delay run by %d , t = %d"), IntParameter, Time);
    while (IntParameter > 0) {
        //for (int i = 0; i < Pins; i++) {
        //    if (PinActive[i] == 1) {
        //        PackageBits[i] += FString::FromInt(PinStatus[i]);
        //    }
        //    else {
        //        PackageBits[i] += "0";
        //    }
        //}
        for (int i = 0; i < Pins; i++) {
            for (int j = 0; j < MaxSpeed; j++) {
                if (PinActive[i] == 1) {
                    if (j < PinSpeed[i]) {
                        SignalBits[i] += FString::FromInt(PinStatus[i]);
                    }
                    else {
                        SignalBits[i] += FString::FromInt(0);
                    }
                }
                else {
                    SignalBits[i] += "0";
                }

            }
        }
        TickCount += 1;
        if (TickCount >= (1000 / Tick)) { //only if 1 full second has passed
            ProgressTick(Package, PackageBits, Time, TickCount, PinStatus, Signal, SignalBits, PinSpeed, PinActive);
        }
        IntParameter = IntParameter - Tick;
    }

}

void UReadWriteSample::ParseFunction(const TArray<FString>& Command, TMap<FString, TArray<FString>>& FunctionDict, TArray<TArray<FString>>& VarStack) {
    FString previousCommand;
    int32 OpenParenIndex, CloseParenIndex;
    TArray<FString> FunctionArray;
    bool functionDetect = false;
    for (int i = 0; i < Command.Num(); i++) {

        if (functionDetect == true) {
            if (!Command[i].Equals("}")) {
                FunctionDict[FunctionArray[1]].Add(Command[i]);
            }
            else {
               functionDetect = false;
            }            
        }
        if (Command[i].Equals("{")) {
            functionDetect = true;
            previousCommand = Command[i - 1];
            if (previousCommand.FindChar('(', OpenParenIndex) && previousCommand.FindChar(')', CloseParenIndex)) {
                // Extract the function name and the parameters inside parentheses
                FString FunctionString = previousCommand.Left(OpenParenIndex).TrimStartAndEnd();
                FString ParametersString = previousCommand.Mid(OpenParenIndex + 1, CloseParenIndex - OpenParenIndex - 1);
                TArray<FString> ParaArray;
                FunctionString.ParseIntoArray(FunctionArray, TEXT(" "), true);
                ParametersString.ParseIntoArray(ParaArray, TEXT(","), true);
                if (FunctionArray.Num() != 2) {
                    break;
                }
                FunctionDict.Add(FunctionArray[1], TArray<FString>());
                FunctionDict.Add(FunctionArray[1]+TEXT("Var"), ParaArray);
            }
        }
        if (functionDetect == false && Command[i].Contains(TEXT("="))) {
            PushVar(Command[i], VarStack);
        }
        
    }  

}



void UReadWriteSample::CallFunction(const FString& FunctionNameIn, TMap<FString, TArray<FString>>& FunctionDict,
    TArray<TArray<FString>>& VarStack, TArray<FString>& Package, TArray<FString>& PackageBits, 
    int32& Time, int32& TickCount, TArray<int32>& PinStatus,TArray<FString>& Signal, 
    TArray<FString>& SignalBits, TArray<int32>& PinSpeed, TArray<int32>& PinActive, FString& compileMessage){

    if (FunctionDict.Contains(FunctionNameIn))
    {
        TArray<FString> FunArray = FunctionDict[FunctionNameIn];
        // Key exists; now you can iterate over or modify the array.
        for (const FString& Command : FunArray)
        {
            if (Time < MaxTimeframe) {
                if (Command.Contains(TEXT("="))) {
                    PushVar(Command, VarStack);
                }
                else 
                {
                int32 OpenParenIndex, CloseParenIndex;
                if (Command.FindChar('(', OpenParenIndex) && Command.FindChar(')', CloseParenIndex)) {
                    // Extract the function name and the parameters inside parentheses
                    FString FunctionName = Command.Left(OpenParenIndex).TrimStartAndEnd();
                    FString ParametersString = Command.Mid(OpenParenIndex + 1, CloseParenIndex - OpenParenIndex - 1);

                    // Split the parameters by comma
                    TArray<FString> ParametersArray;
                    ParametersString.ParseIntoArray(ParametersArray, TEXT(","), true);
                    for (FString& Parameter : ParametersArray)
                    {
                        Parameter = Parameter.TrimStartAndEnd();
                    }
                    if (FunctionName.Equals("pinMode")) {
                        PinMode(ParametersArray, PinActive, VarStack);
                        UE_LOG(LogTemp, Log, TEXT("pinMode Called by %s"), *FunctionNameIn);
                    }
                    else
                        if (FunctionName.Equals("analogWrite")) {
                            AnalogWrite(ParametersArray, PinSpeed, VarStack);
                            UE_LOG(LogTemp, Log, TEXT("analogWrite Called by %s"), *FunctionNameIn);
                        }
                        else
                            if (FunctionName.Equals("digitalWrite")) {
                                DigitalWrite(ParametersArray, PinStatus, VarStack);
                                UE_LOG(LogTemp, Log, TEXT("digitalWrite Called by %s"), *FunctionNameIn);
                            }
                            else
                                if (FunctionName.Equals("delay")) {
                                    Delay(ParametersArray, Package, PackageBits, Time, TickCount,
                                        PinStatus, Signal, SignalBits, PinSpeed, PinActive, VarStack);
                                    UE_LOG(LogTemp, Log, TEXT("delay Called by %s"), *FunctionNameIn);

                                }
                                else {
                                    if (FunctionDict.Contains(FunctionName)) {

                                        TArray<FString> VarArray = FunctionDict[FunctionName + TEXT("Var")];
                                        int32 VarCount = VarArray.Num();
                                        if (ParametersArray.Num() == VarCount) { //type check for passing correct number of variable into function
                                            for (int i = 0; i < VarCount; i++) {
                                                if (ParametersArray[i].IsNumeric()) {
                                                    PushVar(VarArray[i] + TEXT(" = ") + ParametersArray[i], VarStack);
                                                }
                                                else {
                                                    FString VarValue = GetVar(ParametersArray[i], VarStack);
                                                    PushVar(VarArray[i] + TEXT(" = ") + VarValue, VarStack);
                                                }
                                            }
                                            CallFunction(FunctionName, FunctionDict, VarStack, Package, PackageBits,
                                                Time, TickCount, PinStatus, Signal, SignalBits, PinSpeed, PinActive,compileMessage);

                                            PopVar(VarCount, VarStack);
                                        }
                                        else {
                                            UE_LOG(LogTemp, Log, TEXT("Function variable mismatch or missing : "));
                                        }
                                    }
                                    else {
                                        compileMessage = TEXT("Function Not Found: " + FunctionName);
                                        UE_LOG(LogTemp, Log, TEXT("Function Not Found : %s"), *FunctionName);
                                    }
                                }

                }

                }
            }
        }
    }

}

//VarStack related function

// Command format : Declaration Name  = Value;
void UReadWriteSample::PushVar(const FString& Command, TArray<TArray<FString>>& VarStack) {
    TArray<FString> ParametersArray;
    Command.ParseIntoArray(ParametersArray, TEXT("="), true);
    FString assign = ParametersArray[0].TrimStartAndEnd();
    FString val = ParametersArray[1].TrimStartAndEnd();
    assign.ParseIntoArray(ParametersArray, TEXT(" "), true);
    val = val.Replace(TEXT(";"), TEXT("")).TrimStartAndEnd();
    VarStack.Add({ ParametersArray[0], ParametersArray[1], val });
}

// Number of Var to pop
void UReadWriteSample::PopVar(int& VarCount, TArray<TArray<FString>>& VarStack) {
    for (int i = 0; i < VarCount; i++) {
        VarStack.RemoveAt(VarStack.Num() - 1);
    }

}

//VarName to look for value, return the string if found, or return empty string
FString UReadWriteSample::GetVar(const FString& VarName, TArray<TArray<FString>>& VarStack) {
    for (int i = VarStack.Num() - 1; i >= 0; i--) {
        if (VarStack[i][1].Equals(VarName)) {
            return VarStack[i][2];
        }
    }
    UE_LOG(LogTemp, Log, TEXT("Variable Not Found: %s"), *VarName);
    return "";
}



//Print out function
void UReadWriteSample::PrintStringArray(const TArray<FString>& StringArray)
{
    UE_LOG(LogTemp, Log, TEXT("Printing String Array:"));

    for (const FString& Item : StringArray)
    {
        UE_LOG(LogTemp, Log, TEXT("%s"), *Item);
    }
}

void UReadWriteSample::PrintFunctionDict(const TMap<FString, TArray<FString>>& FunctionDict) {
    for (const TPair<FString, TArray<FString>>& Pair : FunctionDict)
    {
        FString Values = FString::Join(Pair.Value, TEXT(", "));
        UE_LOG(LogTemp, Log, TEXT("Key: %s, Values: [%s]"), *Pair.Key, *Values);
    }
}

void UReadWriteSample::PrintVarArray(const TArray<TArray<FString>>& VarArray)
{
    // Check if the array is empty
    if (VarArray.IsEmpty())
    {
        UE_LOG(LogTemp, Warning, TEXT("VarArray is empty!"));
        return;
    }

    // Iterate through each row
    for (int32 RowIndex = 0; RowIndex < VarArray.Num(); RowIndex++)
    {
        // Join the row into a single string for easy logging
        FString RowData = FString::Join(VarArray[RowIndex], TEXT(", "));
        UE_LOG(LogTemp, Log, TEXT("Row %d: [%s]"), RowIndex, *RowData);
    }
}