// Copyright Epic Games, Inc. All Rights Reserved.
using System;
using System.IO;
using UnrealBuildTool;

public class TRUDemo : ModuleRules
{
	public TRUDemo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "LEDBlinkTest" });

		PrivateDependencyModuleNames.AddRange(new string[] { "LEDBlinkTest" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true

		// PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "..", "..", "Plugins", "LEDBlinkTest", "Source", "ThirdParty", "Win64LEDBlinkTest1", "lib", "build", "Win64ReleaseLEDBlinkTest1.lib"));

		// PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "..", "..", "Plugins", "LEDBlinkTest", "Source", "ThirdParty", "Win64LEDBlinkTest1", "lib", "build" "Win64LEDBlinkTest1.lib"));
		
	}
}
