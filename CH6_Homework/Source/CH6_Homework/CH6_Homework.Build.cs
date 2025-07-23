// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CH6_Homework : ModuleRules
{
	public CH6_Homework(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
