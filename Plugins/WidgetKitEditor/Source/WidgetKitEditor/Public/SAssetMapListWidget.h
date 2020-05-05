// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "AssetData.h"
#include "Widgets/Views/STableRow.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "TextAssetEditor/Private/Widgets/STextAssetEditor.h"
#include "RedoUndoStack.h"
#include "EditorStyle.h"
#include "SEditorAsset.h"
#include "TextAsset.h"

class SEditableTextBox;
class str_asset
{
public:
	FString key;
	FAssetData value;
	TSharedPtr<ITableRow> tablerow;
	bool b_canrndo;
};
class WIDGETKITEDITOR_API SAssetMapWidget : public SCompoundWidget
{
	TSharedPtr<str_asset > mstrmap;
	STextAssetEditor* TextAssetEditor;

public:
	SLATE_BEGIN_ARGS(SAssetMapWidget)
	{}
	SLATE_END_ARGS()

		/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs, TSharedPtr<str_asset> strmap, STextAssetEditor* InTextAssetEditor, class SAssetMapListWidget* instringmap_list);
	TSharedPtr<SEditableTextBox> EditableTextBoxkey;
	TSharedPtr<SEditorAsset> EditableTextBoxvalue;
private:
	void OnTextCommittedkey(const FText&, ETextCommit::Type);
	void OnTextCommittedvalue(const FAssetData&);
};
/**
 * 
 */
class WIDGETKITEDITOR_API SAssetMapListWidget : public SCompoundWidget
{
	bool bvisibilitytest = true;
public:
	SLATE_BEGIN_ARGS(SAssetMapListWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
		void Construct(const FArguments& InArgs, STextAssetEditor* InTextAssetEditor) {
		TextAsset = InTextAssetEditor->TextAsset;
		TextAssetEditor = InTextAssetEditor;
		ChildSlot
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
			//.FillHeight(0.2f)
			.AutoHeight()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
			.HAlign(HAlign_Left)
			[
				SNew(SBox)
				.WidthOverride(30)
			.HeightOverride(30)
			[
				SNew(SButton)
				.ButtonStyle(FEditorStyle::Get(), "FlatButton")
			.ContentPadding(FMargin(1, 1, 1, 1))
			.OnClicked_Lambda([this]() {
			bvisibilitytest = !bvisibilitytest;
			return FReply::Handled();
				})
			[
				SNew(STextBlock)
				.TextStyle(FEditorStyle::Get(), "ContentBrowser.TopBar.Font")
					.Font(FEditorStyle::Get().GetFontStyle("FontAwesome.14"))
					.Text(FEditorFontGlyphs::Folder)
			]
			]
			]
		+ SHorizontalBox::Slot()
			.HAlign(HAlign_Center)
			[
				SNew(STextBlock)
				.TextStyle(FEditorStyle::Get(), "ContentBrowser.TopBar.Font")
			//.Font(FEditorStyle::Get().GetFontStyle("FontAwesome.14"))
			.Text(FText::FromString("asset map"))
			]
		+ SHorizontalBox::Slot()
			.HAlign(HAlign_Right)
			[
				SNew(SBox)
				.WidthOverride(30)
				.HeightOverride(30)
				[
					SNew(SButton)
					.ButtonStyle(FEditorStyle::Get(), "FlatButton")
					.ContentPadding(FMargin(1, 1, 1, 1))
					.OnClicked_Lambda([this]() {
						bvisibilitytest = true;
						TSharedPtr<str_asset> tempstr_str = MakeShareable(new str_asset());
						tempstr_str->b_canrndo = true;
						Items.Add(tempstr_str);//when add RequestListRefresh is  necessary
						//Update the listview
						ListViewWidget->RequestListRefresh();
						///////////////////////////////////////////////////////////////////////////////////////////////////////
						//rowAddRNdo* rrndop = new rowAddRNdo();
						//rrndop->mStringMapListWidget = this;
						//rrndop->mstrmap = tempstr_str;
						//TextAssetEditor->TexAssetEditorRedoUndoManager->Undostack->Push(rrndop);
						return FReply::Handled();
					})
					[
						SNew(STextBlock)
						.TextStyle(FEditorStyle::Get(), "ContentBrowser.TopBar.Font")
						.Font(FEditorStyle::Get().GetFontStyle("FontAwesome.14"))
						.Text(FEditorFontGlyphs::Plus_Square)
					]
				]
			]


			]
		+ SVerticalBox::Slot()
			.FillHeight(1.0f)
			[
				SAssignNew(ListViewWidget, SListView<TSharedPtr<str_asset>>)
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
			    .ItemHeight(0.2)
				.ListItemsSource(&Items) //The Items array is the source of this listview
				.OnGenerateRow(this, &SAssetMapListWidget::OnGenerateRowForList)
			]
			];
		initailize();
	}
	void initailize()
	{
		for (TMap<FString , UObject*>::TIterator it = TextAsset->assetmap.CreateIterator(); it; ++it)
		{
			TSharedPtr<str_asset> temp = MakeShareable(new str_asset());
			temp->key = it->Key;
			temp->value = it->Value;
			temp->b_canrndo = false;
			Items.Add(temp);
		}
	}
	void Ondeleterow(TSharedPtr<str_asset> pstr_asset)
	{
		TextAssetEditor->TextAsset->assetmap.Remove(pstr_asset->key);
		Items.Remove(pstr_asset);//when remove RequestListRefresh is not necessary
		TextAssetEditor->TextAsset->MarkPackageDirty();
		////////////////////////////////////////////////////////////////////////////
	}
	TSharedRef<ITableRow> OnGenerateRowForList(TSharedPtr<str_asset> Item, const TSharedRef<STableViewBase>& OwnerTable) {
		TSharedPtr<SAssetMapWidget> TabWidget = SNew(SAssetMapWidget, Item, TextAssetEditor, this);
		if (!Item->b_canrndo)//can not rndo
		{
			return
				SNew(STableRow<TSharedPtr<FString> >, OwnerTable)
				.Padding(1.0f)
				[
					TabWidget.ToSharedRef()
				];
		}
		else//can rndo
		{
			if (Item->tablerow.IsValid())
			{
				return Item->tablerow.ToSharedRef();
			}
			else
			{
				TSharedPtr<ITableRow> temptablerow;
				SAssignNew(temptablerow, STableRow<TSharedPtr<FString> >, OwnerTable)
					.Padding(1.0f)
					[
						TabWidget.ToSharedRef()
					];
				Item->tablerow = temptablerow;
				return
					temptablerow.ToSharedRef();
			}
		}
	}
	UTextAsset* TextAsset;
	STextAssetEditor* TextAssetEditor;
	/* The list of strings */
	TArray<TSharedPtr<str_asset>> Items;
	/* The actual UI list */
	TSharedPtr<SListView<TSharedPtr<str_asset>>> ListViewWidget;
};
