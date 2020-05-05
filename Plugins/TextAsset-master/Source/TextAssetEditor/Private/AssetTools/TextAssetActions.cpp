// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "TextAssetActions.h"

#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "TextAsset.h"
#include "Styling/SlateStyle.h"

#include "TextAssetEditorToolkit.h"
#include "Engine.h"

#define LOCTEXT_NAMESPACE "AssetTypeActions"


/* FTextAssetActions constructors
 *****************************************************************************/

FTextAssetActions::FTextAssetActions(const TSharedRef<ISlateStyle>& InStyle)
	: Style(InStyle)
{ }


/* FAssetTypeActions_Base overrides
 *****************************************************************************/

bool FTextAssetActions::CanFilter()
{
	return true;
}


void FTextAssetActions::GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder)
{
	FAssetTypeActions_Base::GetActions(InObjects, MenuBuilder);
}


uint32 FTextAssetActions::GetCategories()
{
	return EAssetTypeCategories::Misc;
}


FText FTextAssetActions::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_TextAsset", "Text Asset");
}


UClass* FTextAssetActions::GetSupportedClass() const
{
	return UTextAsset::StaticClass();
}


FColor FTextAssetActions::GetTypeColor() const
{
	return FColor::Blue;
}


bool FTextAssetActions::HasActions(const TArray<UObject*>& InObjects) const
{
	return true;
}


void FTextAssetActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid()
		? EToolkitMode::WorldCentric
		: EToolkitMode::Standalone;

	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		auto TextAsset = Cast<UTextAsset>(*ObjIt);

		if (TextAsset != nullptr)
		{
			TSharedRef<FTextAssetEditorToolkit> EditorToolkit = MakeShareable(new FTextAssetEditorToolkit(Style));
			EditorToolkit->Initialize(TextAsset, Mode, EditWithinLevelEditor);
		}
	}
}


#undef LOCTEXT_NAMESPACE
