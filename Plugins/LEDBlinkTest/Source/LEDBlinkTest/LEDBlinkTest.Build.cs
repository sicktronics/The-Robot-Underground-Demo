// Copyright Epic Games, Inc. All Rights Reserved.
using System;
using System.IO;
using UnrealBuildTool;

public class LEDBlinkTest : ModuleRules
{
	public LEDBlinkTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"Win64LEDBlinkTest1"
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"Win64LEDBlinkTest1"
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

			string ThirdPartyPath = Path.Combine(ModuleDirectory, "../ThirdParty/");

			// Include directory
			PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "Win64LEDBlinkTest1/src/CPU"));
			PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "Win64LEDBlinkTest1/src/glueCode"));
			PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "Win64LEDBlinkTest1/src/peripherals"));

			// Library directory
			string LibPath = Path.Combine(ThirdPartyPath, "Win64LEDBlinkTest1/lib/build");

			if (Target.Platform == UnrealTargetPlatform.Win64)
			{
				PublicAdditionalLibraries.Add(Path.Combine(LibPath, "Win64ReleaseLEDBlinkTest1.lib"));
			}
	}
}
