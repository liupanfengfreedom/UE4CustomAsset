// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Templates/SharedPointer.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"
#include "Editor/EditorWidgets/Public/SAssetDropTarget.h"
#include "AssetData.h"
#include "Widgets/Views/SListView.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Input/SButton.h"
#include "Misc/Optional.h"
class FText;
class ISlateStyle;
class UTextAsset;

class SStringlist
	: public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SStringlist)
		//:_Text()
	{ }
	/** The text to display in this button, if no custom content is specified */
	SLATE_ATTRIBUTE(FText, Text1)
	SLATE_ATTRIBUTE(FText, Text2)
	SLATE_EVENT(FOnClicked, OnClicked)
	SLATE_EVENT(FSimpleDelegate, OnHovered)

	SLATE_END_ARGS()
		FText mftexta;
	    FText mftextb;
		/** The delegate to execute when the button is released */
		FSimpleDelegate OnHovered;
		FOnClicked OnClicked;
		bool bvisibilitytest=true;
public:

	/** Virtual destructor. */
	virtual ~SStringlist() {}
	TSharedPtr<SButton> mSButton;
	void Construct(const FArguments& InArgs) {
		mftexta = InArgs._Text1.Get();
		mftextb = InArgs._Text2.Get();
		OnClicked = InArgs._OnClicked;
		OnHovered = InArgs._OnHovered;
		ChildSlot
			[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			//.FillHeight(0.1f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
			    .AutoWidth()
				[
					SNew(SBox)
					.WidthOverride(20)
					.HeightOverride(20)
					[
						SAssignNew(mSButton, SButton)
						.OnClicked_Lambda([this]() {
						Items.Add(MakeShareable(new FString("Hello 23")));
						//Update the listview
						ListViewWidget->RequestListRefresh();
						return FReply::Handled();
							})
					]
				]
				+ SHorizontalBox::Slot()
					.AutoWidth()
				    [
						SNew(SBorder)
						.Padding(5)
						[
							SNew(SBox)
							.WidthOverride(20)
							.HeightOverride(20)
							[
								SNew(SButton)
								.OnClicked_Lambda([this]() {
									bvisibilitytest = !bvisibilitytest;
									return FReply::Handled();
								})
							]
						]
					]
					//The actual list view creation
					//+ SScrollBox::Slot()
					//	[
					//		SAssignNew(ListViewWidget, SListView<TSharedPtr<FString>>)
					//		.ItemHeight(24)
					//		.ListItemsSource(&Items) //The Items array is the source of this listview
					//		.OnGenerateRow(this, &SStringlist::OnGenerateRowForList)
					//	]
			]
		  + SVerticalBox::Slot()
		  .FillHeight(1.0f)
		  [
			  SNew(SHorizontalBox)
			  .Visibility_Lambda([this]()->EVisibility {
					  if (bvisibilitytest)
					  {
						  return EVisibility::Visible;
					  }
					  else
					  {
						  return EVisibility::Collapsed;
					  }
				  })
			  + SHorizontalBox::Slot()
			  [
				  SAssignNew(ListViewWidget, SListView<TSharedPtr<FString>>)
				  .ItemHeight(24)
				  .ListItemsSource(&Items) //The Items array is the source of this listview
				  .OnGenerateRow(this, &SStringlist::OnGenerateRowForList)
			  ]
		  ]
		];
	}
	/* Adds a new textbox with the string to the list */
	TSharedRef<ITableRow> OnGenerateRowForList(TSharedPtr<FString> Item, const TSharedRef<STableViewBase>& OwnerTable) {
		TSharedPtr<STextBlock> TabWidget = SNew(STextBlock);
       // TSharedPtr<SStringlist> TabWidget = SNew(SStringlist);
		TabWidget->SetText(*Item.Get());
		return
			SNew(STableRow< TSharedPtr<FString> >, OwnerTable)
			.Padding(2.0f)
			[
				TabWidget.ToSharedRef()
			];
	}

	/* The list of strings */
	TArray<TSharedPtr<FString>> Items;

	/* The actual UI list */
	TSharedPtr< SListView< TSharedPtr<FString> > > ListViewWidget;
	///////////////////////////////////////////////
	virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override
	{
		OnHovered.ExecuteIfBound();
		return FReply::Unhandled();
	}
};


//////////////////////////////////////////
/**
 * Implements the UTextAsset asset editor widget.
 */
class STextAssetEditor
	: public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(STextAssetEditor) { }
	SLATE_END_ARGS()

public:
	TSharedPtr<class RedoUndoManager> TexAssetEditorRedoUndoManager;
	/** Virtual destructor. */
	virtual ~STextAssetEditor();

	/**
	 * Construct this widget
	 *
	 * @param InArgs The declaration data for this widget.
	 * @param InTextAsset The UTextAsset asset to edit.
	 * @param InStyleSet The style set to use.
	 */
	void Construct(const FArguments& InArgs, UTextAsset* InTextAsset, const TSharedRef<ISlateStyle>& InStyle);
	UTextAsset* TextAsset;
private:

	/** Callback for text changes in the editable text box. */
	void HandleEditableTextBoxTextChanged(const FText& NewText);

	/** Callback for committed text in the editable text box. */
	void HandleEditableTextBoxTextCommitted(const FText& Comment, ETextCommit::Type CommitType);

	/** Callback for property changes in the text asset. */
	void HandleTextAssetPropertyChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent);
	void OnAssetDropped(UObject* InObject);
private:

	/** Holds the editable text box widget. */
	TSharedPtr<SMultiLineEditableTextBox> EditableTextBox;
	//TSharedPtr<class SStringMapListWidget> Stringmap_list;
	//TSharedPtr<class SAssetMapListWidget> Assetgmap_list;
	//TSharedPtr<SPropertyEditorAsset> PropertyEditorAsset;

	/** Pointer to the text asset that is being edited. */

	UObject* mInObject;
	const FSlateBrush* GetThumbnailBorder()const;
	void Construct(const FArguments& Args);
	FReply ButtonPressed();

	/* Adds a new textbox with the string to the list */
	TSharedRef<ITableRow> OnGenerateRowForList(TSharedPtr<FString> Item, const TSharedRef<STableViewBase>& OwnerTable);

	/* The list of strings */
	TArray<TSharedPtr<FString>> Items;

	/* The actual UI list */
	TSharedPtr< SListView< TSharedPtr<FString> > > ListViewWidget;
	TSharedPtr<class SWidget> PrimaryWidget;
	void f1();
	void f2();
	TOptional<float> GetTransformDelta() const;            // display this value
	void TransformDeltaCommited(float newValue, ETextCommit::Type CommitType);   // set value when keyboard input

	float SomeoneFloat;    // this value is displayed in SNumericEntryBox
};
