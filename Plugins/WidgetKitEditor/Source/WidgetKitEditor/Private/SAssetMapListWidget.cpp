// Fill out your copyright notice in the Description page of Project Settings.


#include "SAssetMapListWidget.h"
#include "SlateOptMacros.h"
#include "Misc/MessageDialog.h"
#include "EditorStyle.h"
BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SAssetMapWidget::Construct(const FArguments& InArgs, TSharedPtr<str_asset> strmap, STextAssetEditor* InTextAssetEditor, class SAssetMapListWidget* instringmap_list)
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
		    .OnTextCommitted(this, &SAssetMapWidget::OnTextCommittedkey)
		]
	+ SHorizontalBox::Slot()
		.FillWidth(0.02)
		[
			SNew(SSplitter)

		]
	+ SHorizontalBox::Slot()
		.FillWidth(0.67)
		[
			SAssignNew(EditableTextBoxvalue, SEditorAsset)
			.argAssetdata(mstrmap->value)
		    .Oncommitted(this, &SAssetMapWidget::OnTextCommittedvalue)

		]
	+ SHorizontalBox::Slot()
		.FillWidth(0.025)
		[
			SNew(SButton)
			.ButtonStyle(FEditorStyle::Get(), "FlatButton")
			.OnClicked_Lambda([this, instringmap_list]() {
			instringmap_list->Ondeleterow(mstrmap);
//////////////////////////////////////////////////////////////////////////////////////////////
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
void SAssetMapWidget::OnTextCommittedkey(const FText& text, ETextCommit::Type)
{
	if (mstrmap->key.Equals(text.ToString()))
	{
		return;
	}
	bool bkeyexist = TextAssetEditor->TextAsset->assetmap.Contains(text.ToString());
	if (bkeyexist)
	{
		FText Message = FText::FromString(text.ToString() + " key already exist");
		FText Tile = NSLOCTEXT("Warning", "Warning", "failed");
		FMessageDialog::Open(EAppMsgType::Ok, Message, &Tile);
		EditableTextBoxkey->SetText(FText());
		return;
	}
///////////////////////////////////////////////////////////////////////////////////
	TextAssetEditor->TextAsset->assetmap.Remove(mstrmap->key);
	mstrmap->key = text.ToString();
	TextAssetEditor->TextAsset->assetmap.FindOrAdd(mstrmap->key) = mstrmap->value.GetAsset();
	TextAssetEditor->TextAsset->MarkPackageDirty();
}
void SAssetMapWidget::OnTextCommittedvalue(const FAssetData& adata)
{

	if (mstrmap->value==adata)
	{
		return;
	}

	///////////////////////////////////////////////////////////////////////////////////
	mstrmap->value = adata;
	TextAssetEditor->TextAsset->assetmap.FindOrAdd(mstrmap->key) = adata.GetAsset();
	TextAssetEditor->TextAsset->MarkPackageDirty();
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
