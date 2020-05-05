// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Layout/SSplitter.h"
#include "Widgets/Views/SListView.h"
#include "Widgets/Layout/SScrollBox.h"
#include "TextAsset.h"
#include "TextAssetEditor/Private/Widgets/STextAssetEditor.h"
#include "RedoUndoStack.h"
#include "EditorStyle.h"

class SEditableTextBox;
class str_str
{
public:
	FString key;
	FString value;
	TSharedPtr<ITableRow> tablerow;
	bool b_canrndo;
};
/**
 * 
 */
class WIDGETKITEDITOR_API SStringMapWidget : public SCompoundWidget
{
	TSharedPtr<str_str > mstrmap;
	STextAssetEditor* TextAssetEditor;

public:
	SLATE_BEGIN_ARGS(SStringMapWidget)
	{}
	SLATE_END_ARGS()

		/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs, TSharedPtr<str_str> strmap, STextAssetEditor* InTextAssetEditor, class SStringMapListWidget* instringmap_list);
	TSharedPtr<SEditableTextBox> EditableTextBoxkey;
	TSharedPtr<SEditableTextBox> EditableTextBoxvalue;
private:
	void OnTextCommittedkey(const FText&, ETextCommit::Type);
	void OnTextCommittedvalue(const FText&, ETextCommit::Type);
	class keyChangeRNdo:public RedoUndointerface
	{
	public:
		SStringMapWidget* mStringMapWidget;
		FText newtext;
		FText oldtext;
		void Redo() {
			mStringMapWidget->TextAssetEditor->TextAsset->stringmap.Remove(mStringMapWidget->mstrmap->key);//remove a key-value from asset map
			mStringMapWidget->mstrmap->key = newtext.ToString();
			mStringMapWidget->TextAssetEditor->TextAsset->stringmap.FindOrAdd(mStringMapWidget->mstrmap->key) = mStringMapWidget->mstrmap->value;//add a key-value from asset map
			mStringMapWidget->TextAssetEditor->TextAsset->MarkPackageDirty();
			mStringMapWidget->EditableTextBoxkey->SetText(newtext);
		}
		void Undo() {
			mStringMapWidget->TextAssetEditor->TextAsset->stringmap.Remove(mStringMapWidget->mstrmap->key);//remove a key-value from asset map
			mStringMapWidget->mstrmap->key = oldtext.ToString();
			mStringMapWidget->TextAssetEditor->TextAsset->stringmap.FindOrAdd(mStringMapWidget->mstrmap->key) = mStringMapWidget->mstrmap->value;//add a key-value from asset map
			mStringMapWidget->TextAssetEditor->TextAsset->MarkPackageDirty();
			mStringMapWidget->EditableTextBoxkey->SetText(oldtext);

		}
	};
	class valueChangeRNdo :public RedoUndointerface
	{
	public:
		SStringMapWidget* mStringMapWidget;
		FText newtext;
		FText oldtext;
		void Redo() {
			mStringMapWidget->mstrmap->value = newtext.ToString();
			mStringMapWidget->TextAssetEditor->TextAsset->stringmap.FindOrAdd(mStringMapWidget->mstrmap->key) = newtext.ToString();
			mStringMapWidget->TextAssetEditor->TextAsset->MarkPackageDirty();
			mStringMapWidget->EditableTextBoxvalue->SetText(newtext);
		}
		void Undo() {
			mStringMapWidget->mstrmap->value = oldtext.ToString();
			mStringMapWidget->TextAssetEditor->TextAsset->stringmap.FindOrAdd(mStringMapWidget->mstrmap->key) = oldtext.ToString();
			mStringMapWidget->TextAssetEditor->TextAsset->MarkPackageDirty();
			mStringMapWidget->EditableTextBoxvalue->SetText(oldtext);
		}
	};
};
class WIDGETKITEDITOR_API SStringMapListWidget : public SCompoundWidget
{
	bool bvisibilitytest = true;

public:
	SLATE_BEGIN_ARGS(SStringMapListWidget)
	{}
	SLATE_END_ARGS()

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
				+SHorizontalBox::Slot()
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
					.Text(FText::FromString("string map"))
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
								TSharedPtr<str_str> tempstr_str = MakeShareable(new str_str());
								tempstr_str->b_canrndo = true;
								Items.Add(tempstr_str);//when add RequestListRefresh is  necessary
								//Update the listview
								ListViewWidget->RequestListRefresh();
								///////////////////////////////////////////////////////////////////////////////////////////////////////
								rowAddRNdo* rrndop = new rowAddRNdo();
								rrndop->mStringMapListWidget = this;
								rrndop->mstrmap = tempstr_str;
								TextAssetEditor->TexAssetEditorRedoUndoManager->Undostack->Push(rrndop);
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
				SAssignNew(ListViewWidget, SListView<TSharedPtr<str_str>>)
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
				.OnGenerateRow(this, &SStringMapListWidget::OnGenerateRowForList)
			]
			];
		initailize();
	}
	void initailize()
	{
		for (TMap<FString, FString>::TIterator it = TextAsset->stringmap.CreateIterator(); it; ++it)
		{
			TSharedPtr<str_str> temp = MakeShareable(new str_str());
			temp->key = it->Key;
			temp->value = it->Value;
			temp->b_canrndo = false;
			Items.Add(temp);
		}
	}
	void Ondeleterow(TSharedPtr<str_str> pstr_str)
	{
		TextAssetEditor->TextAsset->stringmap.Remove(pstr_str->key);
		Items.Remove(pstr_str);//when remove RequestListRefresh is not necessary
		TextAssetEditor->TextAsset->MarkPackageDirty();
////////////////////////////////////////////////////////////////////////////
		rowDeleteRNdo* rdrp = new rowDeleteRNdo();
		rdrp->mStringMapListWidget = this;
		rdrp->mstrmap = pstr_str;
		pstr_str->b_canrndo = true;
		TextAssetEditor->TexAssetEditorRedoUndoManager->Undostack->Push(rdrp);
	}
	/* Adds a new textbox with the string to the list */
	TSharedRef<ITableRow> OnGenerateRowForList(TSharedPtr<str_str> Item, const TSharedRef<STableViewBase>& OwnerTable) {
		TSharedPtr<SStringMapWidget> TabWidget = SNew(SStringMapWidget, Item, TextAssetEditor, this);
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
	TArray<TSharedPtr<str_str>> Items;

	/* The actual UI list */
	TSharedPtr<SListView<TSharedPtr<str_str>>> ListViewWidget;
	class rowAddRNdo :public RedoUndointerface
	{
	public:
		SStringMapListWidget* mStringMapListWidget;
		TSharedPtr<str_str > mstrmap;
		void Redo() {
			mStringMapListWidget->Items.Add(mstrmap);//when add RequestListRefresh is  necessary
		     //Update the listview
			mStringMapListWidget->ListViewWidget->RequestListRefresh();
			mStringMapListWidget->TextAssetEditor->TextAsset->stringmap.FindOrAdd(mstrmap->key) = mstrmap->value;
			mStringMapListWidget->TextAssetEditor->TextAsset->MarkPackageDirty();
		}
		void Undo() {
			mStringMapListWidget->TextAssetEditor->TextAsset->stringmap.Remove(mstrmap->key);
			mStringMapListWidget->Items.Remove(mstrmap);//when remove RequestListRefresh is not necessary
			mStringMapListWidget->TextAssetEditor->TextAsset->MarkPackageDirty();
		}
	};
	class rowDeleteRNdo :public RedoUndointerface
	{
	public:
		SStringMapListWidget* mStringMapListWidget;
		TSharedPtr<str_str > mstrmap;
		void Redo() {
			mStringMapListWidget->TextAssetEditor->TextAsset->stringmap.Remove(mstrmap->key);
			mStringMapListWidget->Items.Remove(mstrmap);//when remove RequestListRefresh is not necessary
			mStringMapListWidget->TextAssetEditor->TextAsset->MarkPackageDirty();
		}
		void Undo() {
			mStringMapListWidget->Items.Add(mstrmap);//when add RequestListRefresh is  necessary
		 //Update the listview
			mStringMapListWidget->ListViewWidget->RequestListRefresh();
			mStringMapListWidget->TextAssetEditor->TextAsset->stringmap.FindOrAdd(mstrmap->key) = mstrmap->value;
			mStringMapListWidget->TextAssetEditor->TextAsset->MarkPackageDirty();
		}
	};
};
