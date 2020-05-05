// Fill out your copyright notice in the Description page of Project Settings.


#include "SStringMapListWidget.h"
#include "SlateOptMacros.h"
#include "Misc/MessageDialog.h"
#include "EditorStyle.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SStringMapWidget::Construct(const FArguments& InArgs, TSharedPtr<str_str > strmap, STextAssetEditor* InTextAssetEditor, class SStringMapListWidget* instringmap_list)
{
	mstrmap = strmap;
	TextAssetEditor = InTextAssetEditor;
	ChildSlot
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
		.FillWidth(0.3)
		[
			SAssignNew(EditableTextBoxkey, SEditableTextBox)
			.Text(FText::FromString(mstrmap->key))
		.OnTextCommitted(this, &SStringMapWidget::OnTextCommittedkey)
		]
	+ SHorizontalBox::Slot()
		.FillWidth(0.005)
		[
			SNew(SSplitter)

		]
	+ SHorizontalBox::Slot()
		.FillWidth(0.67)
		[
			SAssignNew(EditableTextBoxvalue, SEditableTextBox)
			.Text(FText::FromString(mstrmap->value))
		    .OnTextCommitted(this, &SStringMapWidget::OnTextCommittedvalue)

		]
	+ SHorizontalBox::Slot()
		.FillWidth(0.025)
		[
			SNew(SButton)
			.ButtonStyle(FEditorStyle::Get(), "FlatButton")
			.OnClicked_Lambda([this, instringmap_list]() {
		        instringmap_list->Ondeleterow(mstrmap);
			     return FReply::Handled();
				})
			[
				SNew(STextBlock)
				.TextStyle(FEditorStyle::Get(), "ContentBrowser.TopBar.Font")
				.Font(FEditorStyle::Get().GetFontStyle("FontAwesome.14"))
				.Text(FEditorFontGlyphs::Times)
			]
		]
		];
}
void SStringMapWidget::OnTextCommittedkey(const FText& text, ETextCommit::Type)
{
	if (mstrmap->key.Equals(text.ToString()))
	{
		return;
	}
	bool bkeyexist = TextAssetEditor->TextAsset->stringmap.Contains(text.ToString());
	if (bkeyexist)
	{
		FText Message = FText::FromString(text.ToString()+" key already exist");
		FText Tile = NSLOCTEXT("Warning", "Warning", "failed");
		FMessageDialog::Open(EAppMsgType::Ok, Message, &Tile);
		EditableTextBoxkey->SetText(FText());
		return;
	}
	keyChangeRNdo* undop = new keyChangeRNdo();
	undop->mStringMapWidget = this;
	undop->newtext = text;
	undop->oldtext = FText::FromString(mstrmap->key);
	TextAssetEditor->TexAssetEditorRedoUndoManager->Undostack->Push(undop);
///////////////////////////////////////////////////////////////////////////////////
	TextAssetEditor->TextAsset->stringmap.Remove(mstrmap->key);
	mstrmap->key = text.ToString();
	TextAssetEditor->TextAsset->stringmap.FindOrAdd(mstrmap->key) = mstrmap->value;
	TextAssetEditor->TextAsset->MarkPackageDirty();
}
void SStringMapWidget::OnTextCommittedvalue(const FText& text, ETextCommit::Type)
{
	if (mstrmap->value.Equals(text.ToString()))
	{
		return;
	}
	valueChangeRNdo* undop = new valueChangeRNdo();
	undop->mStringMapWidget = this;
	undop->newtext = text;
	undop->oldtext = FText::FromString(mstrmap->value);
	TextAssetEditor->TexAssetEditorRedoUndoManager->Undostack->Push(undop);
///////////////////////////////////////////////////////////////////////////////////
	mstrmap->value = text.ToString();
	TextAssetEditor->TextAsset->stringmap.FindOrAdd(mstrmap->key) = text.ToString();
	TextAssetEditor->TextAsset->MarkPackageDirty();
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
