// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class OVERKILL_TD : ModuleRules
{
	public OVERKILL_TD(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule", "Niagara" });
    }
}
