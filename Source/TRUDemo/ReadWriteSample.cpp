// Fill out your copyright notice in the Description page of Project Settings.


#include "ReadWriteSample.h"

#include "HAL/PlatformFileManager.h"
#include "Misc/FileHelper.h"
#include "Misc/DateTime.h"

//SL function
FString UReadWriteSample::SaveUserInput(FString content, int option, int page) {
    FDateTime Now = FDateTime::Now();
    FString TimeString = Now.ToString();
    FString dPath;    

    dPath = FString::Format(
        TEXT("{0}{1}"),
        { FPaths::ProjectDir(),TEXT("TextFile/savefilehead.txt") }
    );
    FString reading = "";
    TArray<FString> Commands;
    FFileHelper::LoadFileToString(reading, *dPath);
    reading.ParseIntoArrayLines(Commands, true);
    for (int i = page *6; i < page*6 +6; i++) {
        if (i == page * 6 + option - 1) {
            Commands[i] = TimeString;
        }
    }
    FString input = "";
    for (const FString& Line : Commands) {
        input += Line + LINE_TERMINATOR;
    }
    FFileHelper::SaveStringToFile(input, *dPath);

    dPath = FString::Format(
        TEXT("{0}{1}{2}{3}"),
        { FPaths::ProjectDir(),TEXT("TextFile/userinput"),page*6 +option,TEXT(".txt")}
    );
    if (FFileHelper::SaveStringToFile(content, *dPath)) {
        return "Save success";
    }
    else {
        return "Save failed";
    }
}

//Template default page number = 0
TArray<FString> UReadWriteSample::LoadSaveHeader(int head, int page) {
    FString dPath;
    if (head == 0) {
        dPath = FString::Format(
            TEXT("{0}{1}"),
            { FPaths::ProjectDir(),TEXT("TextFile/savefilehead.txt") }
        );
    }
    else {
        dPath = FString::Format(
            TEXT("{0}{1}"),
            { FPaths::ProjectDir(),TEXT("TextFile/templatedesc.txt") }
        );
    }

    FString reading = "";
    TArray<FString> Commands;
    FFileHelper::LoadFileToString(reading, *dPath);
    reading.ParseIntoArrayLines(Commands, true);
    for (FString& Line : Commands)
    {
        Line = Line.TrimStartAndEnd();
    }
    TArray<FString> OnePage;

    int32 StartIndex = page *6;
    int32 EndIndex = StartIndex +5;

    for (int32 i = StartIndex; i <= EndIndex && i < Commands.Num(); ++i)
    {
        OnePage.Add(Commands[i]);
    }

    return OnePage;
}

//1-6 for saves, 7-12 for template
FString UReadWriteSample::ReadUserInput(int option, int page) {
    FString dPath;
    if (option < 6) {
        dPath = FString::Format(
            TEXT("{0}{1}{2}{3}"),
            { FPaths::ProjectDir(),TEXT("TextFile/userinput"),page*6+option,TEXT(".txt") }
        );
    }
    else {
        option -= 6;
        dPath = FString::Format(
            TEXT("{0}{1}{2}{3}"),
            { FPaths::ProjectDir(),TEXT("TextFile/template"),option,TEXT(".txt") }
        );
    }    
    if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*dPath)) {

        return	"Save not Found";
    }
    FString reading = "";
    if (!FFileHelper::LoadFileToString(reading, *dPath)) {

        return "Load failed";
    }
    return reading;
}

//Autosave from 1 to 6, load index
int32 UReadWriteSample::AutoIndex() {
    FString dPath = FString::Format(
        TEXT("{0}{1}"),
        { FPaths::ProjectDir(),TEXT("TextFile/autosaveindex.txt") }
    );
    FString reading = "";
    FFileHelper::LoadFileToString(reading, *dPath);
    int32 index;
    index = FCString::Atoi(*reading.TrimStartAndEnd());
    index = index % 6 +1;
    reading = FString::FromInt(index);
    FFileHelper::SaveStringToFile(reading, *dPath);
    return index;
}


//The actual compiler
FString UReadWriteSample::WriteToFile(FString content) {
    int32 index = AutoIndex();
    FString userinput = SaveUserInput(content,index,0);
    //initalize all variable needed
    TMap<FString, TArray<FString>> FunctionDict;
    TArray<TArray<FString>> VarStack;
    TArray<FString> Commands = cleanInput(content);
    FString complieMessage = "Compile success!";
    //PrintStringArray(Commands);
    ParseFunction(Commands, FunctionDict, VarStack, complieMessage);
    //PrintFunctionDict(FunctionDict);
    //PrintVarArray(VarStack);
    TArray<FString> signalResult,signalBits;
    signalBits.SetNum(Pins);
    TArray<int32> pinStatus, pinActive, pinSpeed;
    pinStatus.Init(0, Pins);
    pinActive.Init(0, Pins);
    pinSpeed.Init(0, Pins);
    int32 TickCount = 0, Time = 0;

    //start setup here
    CallFunction(TEXT("setup"), FunctionDict, VarStack,Time, TickCount, pinStatus, 
        signalResult, signalBits, pinSpeed, pinActive, complieMessage);
    FString input = "";
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

void UReadWriteSample::ProgressTick(int32& Time, int32& TickCount, TArray<int32>& PinStatus,
    TArray<FString>& Signal, TArray<FString>& SignalBits, TArray<int32>& PinSpeed , TArray<int32>& PinActive) {
    if (Time == 0) {//header
        Signal.Add(FString("Signal output"));
    }
    while (TickCount < (1000 / Tick)) {  //pad the rest of tick in the time frame
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
    Signal.Add(FString("**********"));
    Signal.Add(FString("t = ") + FString::FromInt(Time));
    for (int i = 0; i < Pins; i++) {
        Signal.Add(FString("pin") + FString::FromInt(i + 1) + FString(" : ") + SignalBits[i]);
        SignalBits[i] = "";
    }
    Time += 1;
    TickCount = 0;
}

//Helper function
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

void UReadWriteSample::PinMode(const TArray<FString>& Para, TArray<int32>& pinActive, TArray<TArray<FString>>& VarStack, FString& compileMessage) {
    if (Para.Num() > 2) {
        return;
    }
    if (!Para[0].IsNumeric()) {
        FString VarValue = GetVar(Para[0], VarStack, compileMessage);
        if (!VarValue.IsEmpty()) {
            pinActive[FCString::Atoi(*VarValue.TrimStartAndEnd()) - 1] = 1;
        }
    }
    if (Para[0].IsNumeric() && Para[1].Equals("OUTPUT", ESearchCase::IgnoreCase)) {
        pinActive[FCString::Atoi(*Para[0].TrimStartAndEnd())-1] = 1;
    }    
}

void UReadWriteSample::AnalogWrite(const TArray<FString>& Para, TArray<int32>& pinSpeed, TArray<TArray<FString>>& VarStack, TArray<int32>& pinStatus, FString& compileMessage) {
    if (Para.Num() > 2) {
        return;
    }
    FString PinValue, SpeedValue;
    int32 PinNumber, SpeedNumber;
    if (!Para[0].IsNumeric()) {
        PinValue = GetVar(Para[0], VarStack, compileMessage);
        PinNumber = FCString::Atoi(*PinValue.TrimStartAndEnd());
    }
    else {
        PinNumber = FCString::Atoi(*Para[0].TrimStartAndEnd());
    }

    if (!Para[1].IsNumeric()) {
        SpeedValue = GetVar(Para[1], VarStack, compileMessage);
        SpeedNumber = FCString::Atoi(*SpeedValue.TrimStartAndEnd());
    }
    else {
        //UE_LOG(LogTemp, Log, TEXT("Speed numberic"));
        SpeedNumber = FCString::Atoi(*Para[1].TrimStartAndEnd());
    }
    //UE_LOG(LogTemp, Log, TEXT("change speed pin : %d to %d"), PinNumber -1, SpeedNumber);
    pinStatus[PinNumber - 1] = 1;
    pinSpeed[PinNumber-1] = SpeedNumber;

}

void UReadWriteSample::DigitalWrite(const TArray<FString>& Para, TArray<int32>& pinStatus, TArray<TArray<FString>>& VarStack, TArray<int32>& pinSpeed, FString& compileMessage) {
    if (Para.Num() > 2) {
        return;
    }
    if (!Para[0].IsNumeric()) {
        FString VarValue = GetVar(Para[0],VarStack, compileMessage);
        if (!VarValue.IsEmpty()) {
            if (Para[1].Contains(TEXT("high"), ESearchCase::IgnoreCase)) {
                pinStatus[FCString::Atoi(*VarValue.TrimStartAndEnd()) - 1] = 1;
                pinSpeed[FCString::Atoi(*VarValue.TrimStartAndEnd()) - 1] = MaxSpeed;
            }
            else
            if (Para[1].Contains(TEXT("low"), ESearchCase::IgnoreCase)) {
                pinStatus[FCString::Atoi(*VarValue.TrimStartAndEnd()) - 1] = 0;
                pinSpeed[FCString::Atoi(*VarValue.TrimStartAndEnd()) - 1] = 0;
            }
        }
    }

    if (Para[0].IsNumeric()) {
        if (Para[1].Contains(TEXT("high"), ESearchCase::IgnoreCase)) {
            pinStatus[FCString::Atoi(*Para[0].TrimStartAndEnd()) - 1] = 1;
            pinSpeed[FCString::Atoi(*Para[0].TrimStartAndEnd()) - 1] = MaxSpeed;
        }
        else if (Para[1].Contains(TEXT("low"), ESearchCase::IgnoreCase)) {
            pinStatus[FCString::Atoi(*Para[0].TrimStartAndEnd()) - 1] = 0;
            pinSpeed[FCString::Atoi(*Para[0].TrimStartAndEnd()) - 1] = 0;
        }
        else {
            return;
        }

    }

}

void UReadWriteSample::Delay(const TArray<FString>& Para, int32& Time, int32& TickCount, TArray<int32>& PinStatus,
    TArray<FString>& Signal, TArray<FString>& SignalBits, TArray<int32>& PinSpeed, TArray<int32>& PinActive, 
    TArray<TArray<FString>>& VarStack, FString& compileMessage) {

    if (Para.Num() > 1) {
        return;
    }
    int32 IntParameter = 0 ;
    if (!Para[0].IsNumeric()) {
        FString VarValue = GetVar(Para[0], VarStack, compileMessage);
        if (!VarValue.IsEmpty()) {
            IntParameter = FCString::Atoi(*VarValue.TrimStartAndEnd());
        }
    }
    else {
        IntParameter = FCString::Atoi(*Para[0].TrimStartAndEnd());
    }

    UE_LOG(LogTemp, Log, TEXT("delay run by %d , t = %d"), IntParameter, Time);
    while (IntParameter > 0) {
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
            ProgressTick(Time, TickCount, PinStatus, Signal, SignalBits, PinSpeed, PinActive);
        }
        IntParameter = IntParameter - Tick;
    }

}

void UReadWriteSample::ParseFunction(const TArray<FString>& Command, TMap<FString, TArray<FString>>& FunctionDict, TArray<TArray<FString>>& VarStack, FString& compileMessage) {
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
                //Name of function , content
                FunctionDict.Add(FunctionArray[1], TArray<FString>());
                FunctionDict.Add(FunctionArray[1]+TEXT("Var"), ParaArray);
            }
        }
        if (functionDetect == false && Command[i].Contains(TEXT("="))) {
            PushVar(Command[i], VarStack, compileMessage);
        }
        
    }  

}



void UReadWriteSample::CallFunction(const FString& FunctionNameIn, TMap<FString, TArray<FString>>& FunctionDict,
    TArray<TArray<FString>>& VarStack, int32& Time, int32& TickCount, TArray<int32>& PinStatus,TArray<FString>& Signal, 
    TArray<FString>& SignalBits, TArray<int32>& PinSpeed, TArray<int32>& PinActive, FString& compileMessage){

    if (FunctionDict.Contains(FunctionNameIn))
    {
        TArray<FString> FunArray = FunctionDict[FunctionNameIn];
        // Key exists; now you can iterate over or modify the array.
        for (const FString& Command : FunArray)
        {
            if (Time < MaxTimeframe) {
                if (Command.Contains(TEXT("="))) {
                    PushVar(Command, VarStack, compileMessage);
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
                        PinMode(ParametersArray, PinActive, VarStack, compileMessage);
                        UE_LOG(LogTemp, Log, TEXT("pinMode Called by %s"), *FunctionNameIn);
                    }
                    else
                        if (FunctionName.Equals("analogWrite")) {
                            AnalogWrite(ParametersArray, PinSpeed, VarStack,PinStatus, compileMessage);
                            UE_LOG(LogTemp, Log, TEXT("analogWrite Called by %s"), *FunctionNameIn);
                        }
                        else
                            if (FunctionName.Equals("digitalWrite")) {
                                DigitalWrite(ParametersArray, PinStatus, VarStack,PinSpeed, compileMessage);
                                UE_LOG(LogTemp, Log, TEXT("digitalWrite Called by %s"), *FunctionNameIn);
                            }
                            else
                                if (FunctionName.Equals("delay")) {
                                    Delay(ParametersArray,Time, TickCount,
                                        PinStatus, Signal, SignalBits, PinSpeed, PinActive, VarStack, compileMessage);
                                    UE_LOG(LogTemp, Log, TEXT("delay Called by %s"), *FunctionNameIn);

                                }
                                else {
                                    if (FunctionDict.Contains(FunctionName)) {

                                        TArray<FString> VarArray = FunctionDict[FunctionName + TEXT("Var")];
                                        int32 VarCount = VarArray.Num();
                                        if (ParametersArray.Num() == VarCount) { //type check for passing correct number of variable into function
                                            for (int i = 0; i < VarCount; i++) {
                                                if (ParametersArray[i].IsNumeric()) {
                                                    PushVar(VarArray[i] + TEXT(" = ") + ParametersArray[i], VarStack, compileMessage);
                                                }
                                                else {
                                                    FString VarValue = GetVar(ParametersArray[i], VarStack, compileMessage);
                                                    PushVar(VarArray[i] + TEXT(" = ") + VarValue, VarStack, compileMessage);
                                                }
                                            }
                                            CallFunction(FunctionName, FunctionDict, VarStack,Time, TickCount, PinStatus, 
                                                Signal, SignalBits, PinSpeed, PinActive,compileMessage);

                                            PopVar(VarCount, VarStack);
                                        }
                                        else {
                                            compileMessage = TEXT("Function variable mismatch or missing : " + FunctionName);
                                            UE_LOG(LogTemp, Log, TEXT("Function variable mismatch or missing"));
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
// If Name = Value, call ChangeVar
void UReadWriteSample::PushVar(const FString& Command, TArray<TArray<FString>>& VarStack, FString& compileMessage) {
    TArray<FString> ParametersArray;
    Command.ParseIntoArray(ParametersArray, TEXT("="), true);
    FString assign = ParametersArray[0].TrimStartAndEnd();
    FString val = ParametersArray[1].TrimStartAndEnd();
    val = val.Replace(TEXT(";"), TEXT("")).TrimStartAndEnd();
    if (!IsNumeric(val)) {
        val = GetVar(val,VarStack, compileMessage);
    }
    assign.ParseIntoArray(ParametersArray, TEXT(" "), true);
    //Declare or change
    if (ParametersArray.Num() == 1) {
        ChangeVar(ParametersArray[0], val, VarStack, compileMessage);
    }
    else {
        VarStack.Add({ ParametersArray[0], ParametersArray[1], val });
    }
}

// Number of Var to pop
void UReadWriteSample::PopVar(int& VarCount, TArray<TArray<FString>>& VarStack) {
    for (int i = 0; i < VarCount; i++) {
        VarStack.RemoveAt(VarStack.Num() - 1);
    }

}

//VarName to look for value, return the string if found, or return empty string
FString UReadWriteSample::GetVar(const FString& VarName, TArray<TArray<FString>>& VarStack, FString& compileMessage) {
    int varIndex = FindVar(VarName,VarStack, compileMessage);
    if (varIndex  >= 0) {
        return VarStack[varIndex][2];
    }
    else
    {
        return "";
    }
}

//Input VarName, return index in VarStack, helper function
int32 UReadWriteSample::FindVar(const FString& VarName, TArray<TArray<FString>>& VarStack, FString& compileMessage) {
    for (int i = VarStack.Num() - 1; i >= 0; i--) {
        if (VarStack[i][1].Equals(VarName)) {
            return i;
        }
    }
    compileMessage = TEXT("Variable Not Found: "+ VarName);
    UE_LOG(LogTemp, Log, TEXT("Variable Not Found: %s"), *VarName);
    return -1;
}

//
void UReadWriteSample::ChangeVar(const FString& VarName, const FString& VarVal,TArray<TArray<FString>>& VarStack, FString& compileMessage) {
    int varIndex = FindVar(VarName, VarStack, compileMessage);
    if (varIndex >= 0) {
        VarStack[varIndex][2] = VarVal;
    }
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