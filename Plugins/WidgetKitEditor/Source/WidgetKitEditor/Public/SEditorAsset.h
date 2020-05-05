// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
DECLARE_DELEGATE_OneParam(FonEditorAssetCommitted, const FAssetData&)
class WIDGETKITEDITOR_API SEditorAsset : public SCompoundWidget
{
	/** The class of the object we are editing */
	FAssetData mAssetdata;
	TSharedPtr< class SBorder > ThumbnailBorder;
	/** Thumbnail for the asset */
	//TSharedRef<FAssetThumbnail> AssetThumbnail;
	TSharedPtr<FAssetThumbnail> AssetThumbnail;
	TSharedPtr< class SComboButton > AssetComboButton;
	TArray<FAssetData> OwnerAssetDataArray;
	FonEditorAssetCommitted Oncommitted;
public:
	SLATE_BEGIN_ARGS(SEditorAsset)
	{}
	SLATE_ATTRIBUTE(FAssetData, argAssetdata)
	SLATE_EVENT(FonEditorAssetCommitted, Oncommitted)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	void OnOpenAssetEditor();
	void OnAssetSelected(const struct FAssetData& AssetData);
	void CloseComboButton();
	void SetAsset(const FAssetData& passet);
	void OnUse();
	void OnBrowse();
	FText GetOnBrowseToolTip() const;

};
