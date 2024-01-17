// Copyright (C) 2024 owoDra

using UnrealBuildTool;

public class GCItemEditor : ModuleRules
{
	public GCItemEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;	

		PublicIncludePaths.AddRange(
            new string[] 
			{
                ModuleDirectory,
                ModuleDirectory + "/GCItemEditor",
            }
        );			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
                "UnrealEd",
                "Slate",
				"SlateCore",
				"UMG",
			}
		);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"ApplicationCore",
				"PropertyPath",
                "DeveloperSettings",
                "ToolWidgets",
                "ClassViewer",
                "AssetTools",
                "GCItem",
            }
		);
	}
}
