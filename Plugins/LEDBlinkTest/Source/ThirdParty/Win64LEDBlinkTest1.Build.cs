// Copyright 1998-2025 Epic Games, Inc. All Rights Reserved.

using System.IO;
using System;

namespace UnrealBuildTool.Rules
{
    public class Win64LEDBlinkTest1 : ModuleRules
    {
        private string ModulePath
        {
            get { return ModuleDirectory; }
        }

        private string BinariesPath
        {
            get { return Path.GetFullPath(Path.Combine(ModulePath, "../Binaries/")); }
        }

        public Win64LEDBlinkTest1(ReadOnlyTargetRules Target) : base(Target)
        {
            // Tell Unreal that this Module only imports Third-Party-Assets
            Type = ModuleType.External;

            LoadWin64LEDBlinkTest1(Target);
        }

        public bool LoadWin64LEDBlinkTest1(ReadOnlyTargetRules Target)
        {
            bool isLibrarySupported = false;
            // bool bDebug = (Target.Configuration == UnrealTargetConfiguration.Debug && BuildConfiguration.bDebugBuildsActuallyUseDebugCRT);

            if (Target.Platform == UnrealTargetPlatform.Win64)
            {
                isLibrarySupported = true;

                //string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "x64" : "x86";

                // Explicitly name the used libraries
                PublicAdditionalLibraries.Add(Path.Combine(ModulePath, "Win64LEDBlinkTest1/lib/build/Win64ReleaseLEDBlinkTest1.lib"));
            }

            if (isLibrarySupported)
            {
                PublicIncludePaths.Add(Path.Combine(ModulePath, "Win64LEDBlinkTest1/src"));

                // Not sure if needed
                // Definitions.Add("_CRT_SECURE_NO_WARNINGS=1");
                // Definitions.Add("BOOST_DISABLE_ABI_HEADERS=1");

                // Needed configurations in order to run Boost
                // bUseRTTI = true;
                // bEnableExceptions = true;
                //bEnableUndefinedIdentifierWarnings = false;
            }

            // Definitions.Add(string.Format("WITH_PCL_BINDING={0}", isLibrarySupported ? 1 : 0));
            // Definitions.Add(string.Format("WITH_BOOST_BINDING={0}", isLibrarySupported ? 1 : 0));

            return isLibrarySupported;
        }
    }
}