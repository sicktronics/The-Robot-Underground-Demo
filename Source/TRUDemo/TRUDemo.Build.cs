// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TRUDemo : ModuleRules
{
	public TRUDemo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

		// Explicitly including the LEDBlinkTest plugin module here
		// LEDBlinkTest internally includes the static library per its own .Build.cs
		PrivateDependencyModuleNames.AddRange(new string[] { "LEDBlinkTest" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
