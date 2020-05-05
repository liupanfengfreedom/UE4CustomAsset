// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using System.IO;
using System.Reflection;
using UnrealBuildTool;

public class WidgetKitEditor : ModuleRules
{
	public WidgetKitEditor(ReadOnlyTargetRules Target) : base(Target)
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
				"TextAssetEditor",
				"Core",
				"EditorUtility",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"UnrealEd",
				"AssetTools",
				"InputCore",
				"TextAsset",
				"TextAssetEditor",
				"PropertyEditor",
				"SlateCore",//EditorWidgets
				"EditorWidgets",//EditorWidgets
				"EditorStyle",//EditorWidgets
			
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);


	}
}
