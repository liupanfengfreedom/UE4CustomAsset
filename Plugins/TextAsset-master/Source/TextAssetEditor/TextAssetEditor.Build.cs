// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TextAssetEditor : ModuleRules
{
	public TextAssetEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        DynamicallyLoadedModuleNames.AddRange(
            new string[] {
                "AssetTools",
                "MainFrame",
                "WorkspaceMenuStructure",
            });

        PrivateIncludePaths.AddRange(
			new string[] {
				"TextAssetEditor/Private",
				"TextAssetEditor/Private/AssetTools",
				"TextAssetEditor/Private/Factories",
				"TextAssetEditor/Private/Shared",
				"TextAssetEditor/Private/Styles",
				"TextAssetEditor/Private/Toolkits",
				"TextAssetEditor/Private/Widgets",
			});
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
			    "Core",
				"EditorWidgets",

				// ... add other public dependencies that you statically link with here ...
			}
			);
		PrivateDependencyModuleNames.AddRange(
			new string[] {
				"ContentBrowser",
				"Core",
				"CoreUObject",
				"DesktopWidgets",
				"EditorStyle",
				"Engine",
				"InputCore",
				"Projects",
				"Slate",
				"SlateCore",
				"TextAsset",
				"PropertyEditor",
				"WidgetKitEditor",
				"UnrealEd",//PropertyEditor.Build
				"EditorUtility",//PropertyEditor.Build
			});

        PrivateIncludePathModuleNames.AddRange(
            new string[] {
                "AssetTools",
                "UnrealEd",
				"PropertyEditor",

//				"WorkspaceMenuStructure",
			});
    }
}
