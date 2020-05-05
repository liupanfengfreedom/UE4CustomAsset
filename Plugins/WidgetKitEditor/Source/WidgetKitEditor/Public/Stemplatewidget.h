// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SBoxPanel.h"
#include "AssetData.h"
#include "Widgets/Views/STableRow.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "TextAssetEditor/Private/Widgets/STextAssetEditor.h"
#include "RedoUndoStack.h"
#include "EditorStyle.h"
#include "SEditorAsset.h"
#include "TextAsset.h"
#include "SEditorAsset.h"
#include "SVectorWidget.h"

#include <type_traits>
#include "Widgets/SCompoundWidget.h"

class str_value
{
public:
	FString key;
	FString stringvalue;
	float floatvalue;
	FVector vectorvalue;
	FAssetData assetvalue;
	TSharedPtr<ITableRow> tablerow;
	bool b_canrndo;
};
class Ikeyvlaueinterface
{
public:
	virtual void Onkeyvaluelistdeleterow(TSharedPtr<str_value> sv) = 0;
};
/**
 * 
 */
template<typename ItemType>
class  Stemplatewidget : public SCompoundWidget
{
public:
	////////////////////////////////////////
	STextAssetEditor* TextAssetEditor;
	TSharedPtr<SEditableTextBox> EditableTextBoxkey;
	TSharedPtr<str_value > mstrmap;

////////////////////////////////////////////////////
	TSharedPtr<SEditableTextBox> StringvalueWidget;
	TSharedPtr<SSpinBox<float>>  floatvalueWidget;
	TSharedPtr<SVectorWidget>  vectorvalueWidget;
	TSharedPtr<SEditorAsset>  assetvalueWidget;

public:
	SLATE_BEGIN_ARGS(Stemplatewidget<ItemType>)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	//void Construct(const FArguments& InArgs)
	void Construct(const FArguments& InArgs, TSharedPtr<str_value> keyvaluemap, STextAssetEditor* InTextAssetEditor , Ikeyvlaueinterface* keyvlaueinterface)
	{
		TSharedRef<SHorizontalBox> horizontalbox = SNew(SHorizontalBox);
		
		mstrmap = keyvaluemap;
		TextAssetEditor = InTextAssetEditor;
		ChildSlot
			[
			  SNew(SHorizontalBox)
			  + SHorizontalBox::Slot()
				.AutoWidth()
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Center)
				[
			         SNew(STextBlock)
					 .Text(FText::FromString("Key:"))
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
			    .HAlign(HAlign_Center)
			    .VAlign(VAlign_Center)
				[
					SNew(SBox)
					.MinDesiredWidth(100)
			        .HeightOverride(20)
					[
						SAssignNew(EditableTextBoxkey, SEditableTextBox)
						.Text(FText::FromString(mstrmap->key))
						.OnTextCommitted_Lambda([this](const FText& text, ETextCommit::Type) {
							if (mstrmap->key.Equals(text.ToString()))
							{
								return;
							}

							bool bkeyexist = false;
							if (std::is_same<ItemType, FString>::value)
							{
								bkeyexist = TextAssetEditor->TextAsset->stringmap.Contains(text.ToString());
								if (bkeyexist)
								{
									FText Message = FText::FromString(text.ToString() + " key already exist");
									FText Tile = NSLOCTEXT("Warning", "Warning", "failed");
									FMessageDialog::Open(EAppMsgType::Ok, Message, &Tile);
									EditableTextBoxkey->SetText(FText());
									return;
								}
								keyChangeRNdo<FString>* undop = new keyChangeRNdo<FString>();
								undop->mtemplatewidget = this;
								undop->newtext = text;
								undop->oldtext = FText::FromString(mstrmap->key);
								TextAssetEditor->TexAssetEditorRedoUndoManager->Undostack->Push(undop);
								///////////////////////////////////////////////////////////////////////////////////
								TextAssetEditor->TextAsset->stringmap.Remove(mstrmap->key);
								mstrmap->key = text.ToString();
								TextAssetEditor->TextAsset->stringmap.FindOrAdd(mstrmap->key) = mstrmap->stringvalue;
								TextAssetEditor->TextAsset->MarkPackageDirty();
							}
							else if (std::is_same<ItemType, float>::value)
							{
								bkeyexist = TextAssetEditor->TextAsset->floatmap.Contains(text.ToString());
								if (bkeyexist)
								{
									FText Message = FText::FromString(text.ToString() + " key already exist");
									FText Tile = NSLOCTEXT("Warning", "Warning", "failed");
									FMessageDialog::Open(EAppMsgType::Ok, Message, &Tile);
									EditableTextBoxkey->SetText(FText());
									return;
								}
								keyChangeRNdo<float>* undop = new keyChangeRNdo<float>();
								undop->mtemplatewidget = this;
								undop->newtext = text;
								undop->oldtext = FText::FromString(mstrmap->key);
								TextAssetEditor->TexAssetEditorRedoUndoManager->Undostack->Push(undop);
								///////////////////////////////////////////////////////////////////////////////////
								TextAssetEditor->TextAsset->floatmap.Remove(mstrmap->key);
								mstrmap->key = text.ToString();
								TextAssetEditor->TextAsset->floatmap.FindOrAdd(mstrmap->key) = mstrmap->floatvalue;
								TextAssetEditor->TextAsset->MarkPackageDirty();
							}
							else if (std::is_same<ItemType, FVector>::value)
							{
								bkeyexist = TextAssetEditor->TextAsset->vectormap.Contains(text.ToString());
								if (bkeyexist)
								{
									FText Message = FText::FromString(text.ToString() + " key already exist");
									FText Tile = NSLOCTEXT("Warning", "Warning", "failed");
									FMessageDialog::Open(EAppMsgType::Ok, Message, &Tile);
									EditableTextBoxkey->SetText(FText());
									return;
								}
								keyChangeRNdo<FVector>* undop = new keyChangeRNdo<FVector>();
								undop->mtemplatewidget = this;
								undop->newtext = text;
								undop->oldtext = FText::FromString(mstrmap->key);
								TextAssetEditor->TexAssetEditorRedoUndoManager->Undostack->Push(undop);
								///////////////////////////////////////////////////////////////////////////////////
								TextAssetEditor->TextAsset->vectormap.Remove(mstrmap->key);
								mstrmap->key = text.ToString();
								TextAssetEditor->TextAsset->vectormap.FindOrAdd(mstrmap->key) = mstrmap->vectorvalue;
								TextAssetEditor->TextAsset->MarkPackageDirty();
							}
							else if (std::is_same<ItemType, UObject*>::value)
							{
								bkeyexist = TextAssetEditor->TextAsset->assetmap.Contains(text.ToString());
								if (bkeyexist)
								{
									FText Message = FText::FromString(text.ToString() + " key already exist");
									FText Tile = NSLOCTEXT("Warning", "Warning", "failed");
									FMessageDialog::Open(EAppMsgType::Ok, Message, &Tile);
									EditableTextBoxkey->SetText(FText());
									return;
								}
								keyChangeRNdo<UObject*>* undop = new keyChangeRNdo<UObject*>();
								undop->mtemplatewidget = this;
								undop->newtext = text;
								undop->oldtext = FText::FromString(mstrmap->key);
								TextAssetEditor->TexAssetEditorRedoUndoManager->Undostack->Push(undop);
								///////////////////////////////////////////////////////////////////////////////////
								TextAssetEditor->TextAsset->assetmap.Remove(mstrmap->key);
								mstrmap->key = text.ToString();
								TextAssetEditor->TextAsset->assetmap.FindOrAdd(mstrmap->key) = mstrmap->assetvalue.GetAsset();
								TextAssetEditor->TextAsset->MarkPackageDirty();
							}
						}
						)
					]
				]
		+ SHorizontalBox::Slot()
			.FillWidth(0.03)
			[
				SNew(SSplitter)

			]
		+ SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(FText::FromString("Value:"))
			]
		+ SHorizontalBox::Slot()
			.FillWidth(0.67)
			[
				horizontalbox
			]
		+ SHorizontalBox::Slot()
			//.FillWidth(0.025)
			//.Padding(0,0,500,0)
			.HAlign(HAlign_Left)
			[
				SNew(SButton)
				.ButtonStyle(FEditorStyle::Get(), "FlatButton")
			    .OnClicked_Lambda([this, keyvlaueinterface]() {
					 keyvlaueinterface->Onkeyvaluelistdeleterow(mstrmap);
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
		if (std::is_same<ItemType, FString>::value)
		{
			horizontalbox->AddSlot()
				.VAlign(VAlign_Center)
				.AutoWidth()
				.Padding(2.0f, 0.0f)
				[
					SNew(SBox)
					.MinDesiredHeight(20)
					.MinDesiredWidth(100)
					[
						SAssignNew(StringvalueWidget, SEditableTextBox)
						.Text(FText::FromString(mstrmap->stringvalue))
				        .OnTextCommitted_Lambda([this](const FText& text, ETextCommit::Type) {
								if (mstrmap->stringvalue.Equals(text.ToString()))
								{
									return;
								}
								valueChangeRNdo<FString>* undop = new valueChangeRNdo<FString>();
								undop->mtemplatewidget = this;
								undop->newtext = text;
								undop->oldtext = FText::FromString(mstrmap->stringvalue);
								TextAssetEditor->TexAssetEditorRedoUndoManager->Undostack->Push(undop);
								///////////////////////////////////////////////////////////////////////////////////
								mstrmap->stringvalue = text.ToString();
								TextAssetEditor->TextAsset->stringmap.FindOrAdd(mstrmap->key) = text.ToString();
								TextAssetEditor->TextAsset->MarkPackageDirty();
					     })
					]

				];
		}
		else if (std::is_same<ItemType, float>::value)
		{
			horizontalbox->AddSlot()
				.VAlign(VAlign_Center)
				//.FillWidth()
				.AutoWidth()
				.Padding(2.0f, 0.0f)
				[
					SNew(SBox)
					.MinDesiredHeight(20)
					.MinDesiredWidth(100)
					[
						SAssignNew(floatvalueWidget, SSpinBox<float>)
						.Value(mstrmap->floatvalue)
						.OnValueCommitted_Lambda([this](float v, ETextCommit::Type type) {
							if (mstrmap->floatvalue == v)
							{
								return;
							}
							valueChangeRNdo<float>* undop = new valueChangeRNdo<float>();
							undop->mtemplatewidget = this;
							undop->newfloat = v;
							undop->oldfloat =mstrmap->floatvalue;
							TextAssetEditor->TexAssetEditorRedoUndoManager->Undostack->Push(undop);
							///////////////////////////////////////////////////////////////////////////////////
							mstrmap->floatvalue = v;
							TextAssetEditor->TextAsset->floatmap.FindOrAdd(mstrmap->key) = v;
							TextAssetEditor->TextAsset->MarkPackageDirty();
						})
					]
					
				];
		}
		else if (std::is_same<ItemType, FVector>::value)
		{
			horizontalbox->AddSlot()
				.VAlign(VAlign_Center)
				//.FillWidth()
				.AutoWidth()
				.Padding(2.0f, 0.0f)
				[
					SNew(SBox)
					.MinDesiredHeight(20)
					.MinDesiredWidth(100)
					[
						SAssignNew(vectorvalueWidget, SVectorWidget)
						.X(mstrmap->vectorvalue.X)
						.Y(mstrmap->vectorvalue.Y)
						.Z(mstrmap->vectorvalue.Z)
						.OncommittedX_Lambda([this](float v) {
							if (mstrmap->vectorvalue.X == v)
							{
								return;
							}
							valueChangeRNdo<FVector>* undop = new valueChangeRNdo<FVector>();
							undop->mtemplatewidget = this;
							undop->newvector = undop->oldvector = mstrmap->vectorvalue;
							undop->newvector.X = v;
							undop->oldvector.X = mstrmap->vectorvalue.X;
							TextAssetEditor->TexAssetEditorRedoUndoManager->Undostack->Push(undop);
							///////////////////////////////////////////////////////////////////////////////////
							mstrmap->vectorvalue.X = v;
							TextAssetEditor->TextAsset->vectormap.FindOrAdd(mstrmap->key).X = v;
							TextAssetEditor->TextAsset->MarkPackageDirty();
						})
						.OncommittedY_Lambda([this](float v) {
							if (mstrmap->vectorvalue.Y == v)
							{
								return;
							}
							valueChangeRNdo<FVector>* undop = new valueChangeRNdo<FVector>();
							undop->mtemplatewidget = this;
							undop->newvector = undop->oldvector = mstrmap->vectorvalue;
							undop->newvector.Y = v;
							undop->oldvector.Y = mstrmap->vectorvalue.Y;
							TextAssetEditor->TexAssetEditorRedoUndoManager->Undostack->Push(undop);
							///////////////////////////////////////////////////////////////////////////////////
							mstrmap->vectorvalue.Y = v;
							TextAssetEditor->TextAsset->vectormap.FindOrAdd(mstrmap->key).Y = v;
							TextAssetEditor->TextAsset->MarkPackageDirty();
					    })
						.OncommittedZ_Lambda([this](float v) {
							if (mstrmap->vectorvalue.Z == v)
							{
								return;
							}
							valueChangeRNdo<FVector>* undop = new valueChangeRNdo<FVector>();
							undop->mtemplatewidget = this;
							undop->newvector = undop->oldvector = mstrmap->vectorvalue;
							undop->newvector.Z = v;
							undop->oldvector.Z = mstrmap->vectorvalue.Z;
							TextAssetEditor->TexAssetEditorRedoUndoManager->Undostack->Push(undop);
							///////////////////////////////////////////////////////////////////////////////////
							mstrmap->vectorvalue.Z = v;
							TextAssetEditor->TextAsset->vectormap.FindOrAdd(mstrmap->key).Z = v;
							TextAssetEditor->TextAsset->MarkPackageDirty();
						})
					]

				];
		}
		else if (std::is_same<ItemType, UObject*>::value)
		{
			horizontalbox->AddSlot()
				.VAlign(VAlign_Center)
				.AutoWidth()
				.Padding(2.0f, 0.0f)
				[
					SAssignNew(assetvalueWidget, SEditorAsset)
					.argAssetdata(mstrmap->assetvalue)
					.Oncommitted_Lambda([this](const FAssetData& adata) {
						if (mstrmap->assetvalue == adata)
						{
							return;
						}
						valueChangeRNdo<UObject*>* undop = new valueChangeRNdo<UObject*>();
						undop->mtemplatewidget = this;
						undop->newObject= adata.GetAsset();
						undop->oldObject = mstrmap->assetvalue.GetAsset();
						TextAssetEditor->TexAssetEditorRedoUndoManager->Undostack->Push(undop);
						///////////////////////////////////////////////////////////////////////////////////
						mstrmap->assetvalue = adata;
						TextAssetEditor->TextAsset->assetmap.FindOrAdd(mstrmap->key) = adata.GetAsset();
						TextAssetEditor->TextAsset->MarkPackageDirty();
					})
				];
		}
		
	}
};
template<typename TemplateType>
class keyChangeRNdo :public RedoUndointerface
{
	
public:	
	void* mtemplatewidget;
	//Stemplatewidget* mtemplatewidget;
	FText newtext;
	FText oldtext;

	void Redo() {

		if (std::is_same<TemplateType, FString>::value)
		{
			Stemplatewidget<FString>* tempstringp = (Stemplatewidget<FString>*)mtemplatewidget;
			tempstringp->TextAssetEditor->TextAsset->stringmap.Remove(tempstringp->mstrmap->key);//remove a key-value from asset map
			tempstringp->mstrmap->key = newtext.ToString();
			tempstringp->TextAssetEditor->TextAsset->stringmap.FindOrAdd(tempstringp->mstrmap->key) = tempstringp->mstrmap->stringvalue;//add a key-value from asset map
			tempstringp->TextAssetEditor->TextAsset->MarkPackageDirty();
			tempstringp->EditableTextBoxkey->SetText(newtext);
		}
		else if (std::is_same<TemplateType, float>::value)
		{
			Stemplatewidget<float>* tempstringp = (Stemplatewidget<float>*)mtemplatewidget;
			tempstringp->TextAssetEditor->TextAsset->floatmap.Remove(tempstringp->mstrmap->key);//remove a key-value from asset map
			tempstringp->mstrmap->key = newtext.ToString();
			tempstringp->TextAssetEditor->TextAsset->floatmap.FindOrAdd(tempstringp->mstrmap->key) = tempstringp->mstrmap->floatvalue;//add a key-value from asset map
			tempstringp->TextAssetEditor->TextAsset->MarkPackageDirty();
			tempstringp->EditableTextBoxkey->SetText(newtext);
		}
		else if (std::is_same<TemplateType, FVector>::value)
		{
			Stemplatewidget<FVector>* tempstringp = (Stemplatewidget<FVector>*)mtemplatewidget;
			tempstringp->TextAssetEditor->TextAsset->vectormap.Remove(tempstringp->mstrmap->key);//remove a key-value from asset map
			tempstringp->mstrmap->key = newtext.ToString();
			tempstringp->TextAssetEditor->TextAsset->vectormap.FindOrAdd(tempstringp->mstrmap->key) = tempstringp->mstrmap->vectorvalue;//add a key-value from asset map
			tempstringp->TextAssetEditor->TextAsset->MarkPackageDirty();
			tempstringp->EditableTextBoxkey->SetText(newtext);
		}
		else if (std::is_same<TemplateType, UObject*>::value)
		{
			Stemplatewidget<UObject*>* tempstringp = (Stemplatewidget<UObject*>*)mtemplatewidget;
			tempstringp->TextAssetEditor->TextAsset->assetmap.Remove(tempstringp->mstrmap->key);//remove a key-value from asset map
			tempstringp->mstrmap->key = newtext.ToString();
			tempstringp->TextAssetEditor->TextAsset->assetmap.FindOrAdd(tempstringp->mstrmap->key) = tempstringp->mstrmap->assetvalue.GetAsset();//add a key-value from asset map
			tempstringp->TextAssetEditor->TextAsset->MarkPackageDirty();
			tempstringp->EditableTextBoxkey->SetText(newtext);
		}
	}
	void Undo() {	
		if (std::is_same<TemplateType, FString>::value)
		{
			Stemplatewidget<FString>* tempstringp = (Stemplatewidget<FString>*)mtemplatewidget;
			tempstringp->TextAssetEditor->TextAsset->stringmap.Remove(tempstringp->mstrmap->key);//remove a key-value from asset map
			tempstringp->mstrmap->key = oldtext.ToString();
			tempstringp->TextAssetEditor->TextAsset->stringmap.FindOrAdd(tempstringp->mstrmap->key) = tempstringp->mstrmap->stringvalue;//add a key-value from asset map
			tempstringp->TextAssetEditor->TextAsset->MarkPackageDirty();
			tempstringp->EditableTextBoxkey->SetText(oldtext);
		}
		else if (std::is_same<TemplateType, float>::value)
		{
			Stemplatewidget<float>* tempstringp = (Stemplatewidget<float>*)mtemplatewidget;
			tempstringp->TextAssetEditor->TextAsset->floatmap.Remove(tempstringp->mstrmap->key);//remove a key-value from asset map
			tempstringp->mstrmap->key = oldtext.ToString();
			tempstringp->TextAssetEditor->TextAsset->floatmap.FindOrAdd(tempstringp->mstrmap->key) = tempstringp->mstrmap->floatvalue;//add a key-value from asset map
			tempstringp->TextAssetEditor->TextAsset->MarkPackageDirty();
			tempstringp->EditableTextBoxkey->SetText(oldtext);
		}
		else if (std::is_same<TemplateType, FVector>::value)
		{
			Stemplatewidget<FVector>* tempstringp = (Stemplatewidget<FVector>*)mtemplatewidget;
			tempstringp->TextAssetEditor->TextAsset->vectormap.Remove(tempstringp->mstrmap->key);//remove a key-value from asset map
			tempstringp->mstrmap->key = oldtext.ToString();
			tempstringp->TextAssetEditor->TextAsset->vectormap.FindOrAdd(tempstringp->mstrmap->key) = tempstringp->mstrmap->vectorvalue;//add a key-value from asset map
			tempstringp->TextAssetEditor->TextAsset->MarkPackageDirty();
			tempstringp->EditableTextBoxkey->SetText(oldtext);
		}
		else if (std::is_same<TemplateType, UObject*>::value)
		{
			Stemplatewidget<UObject*>* tempstringp = (Stemplatewidget<UObject*>*)mtemplatewidget;
			tempstringp->TextAssetEditor->TextAsset->assetmap.Remove(tempstringp->mstrmap->key);//remove a key-value from asset map
			tempstringp->mstrmap->key = oldtext.ToString();
			tempstringp->TextAssetEditor->TextAsset->assetmap.FindOrAdd(tempstringp->mstrmap->key) = tempstringp->mstrmap->assetvalue.GetAsset();//add a key-value from asset map
			tempstringp->TextAssetEditor->TextAsset->MarkPackageDirty();
			tempstringp->EditableTextBoxkey->SetText(oldtext);
		}

	}
};
template<typename TemplateType>
class valueChangeRNdo :public RedoUndointerface
{
public:
	void* mtemplatewidget;
	FText newtext;
	FText oldtext;
	float newfloat;
	float oldfloat;
	FVector newvector;
	FVector oldvector;
	UObject* newObject;
	UObject* oldObject;
	void Redo() {
		if (std::is_same<TemplateType, FString>::value)
		{
			Stemplatewidget<FString>* tempstringp = (Stemplatewidget<FString>*)mtemplatewidget;
			tempstringp->mstrmap->stringvalue = newtext.ToString();
			tempstringp->TextAssetEditor->TextAsset->stringmap.FindOrAdd(tempstringp->mstrmap->key) = newtext.ToString();
			tempstringp->TextAssetEditor->TextAsset->MarkPackageDirty();
			tempstringp->StringvalueWidget->SetText(newtext);
		}
		else if (std::is_same<TemplateType, float>::value)
		{
			Stemplatewidget<float>* tempstringp = (Stemplatewidget<float>*)mtemplatewidget;
			tempstringp->mstrmap->floatvalue = newfloat;
			tempstringp->TextAssetEditor->TextAsset->floatmap.FindOrAdd(tempstringp->mstrmap->key) = newfloat;
			tempstringp->TextAssetEditor->TextAsset->MarkPackageDirty();
			tempstringp->floatvalueWidget->SetValue(newfloat);
		}
		else if (std::is_same<TemplateType, FVector>::value)
		{
			Stemplatewidget<FVector>* tempstringp = (Stemplatewidget<FVector>*)mtemplatewidget;
			tempstringp->mstrmap->vectorvalue = newvector;
			tempstringp->TextAssetEditor->TextAsset->vectormap.FindOrAdd(tempstringp->mstrmap->key) = newvector;
			tempstringp->TextAssetEditor->TextAsset->MarkPackageDirty();
			tempstringp->vectorvalueWidget->SetValue(newvector);
		}
		else if (std::is_same<TemplateType, UObject*>::value)
		{
			Stemplatewidget<UObject*>* tempstringp = (Stemplatewidget<UObject*>*)mtemplatewidget;
			tempstringp->mstrmap->assetvalue = newObject;
			tempstringp->TextAssetEditor->TextAsset->assetmap.FindOrAdd(tempstringp->mstrmap->key) = newObject;
			tempstringp->TextAssetEditor->TextAsset->MarkPackageDirty();
			tempstringp->assetvalueWidget->SetAsset(newObject);
		}
	}
	void Undo() {
		if (std::is_same<TemplateType, FString>::value)
		{
			Stemplatewidget<FString>* tempstringp = (Stemplatewidget<FString>*)mtemplatewidget;
			tempstringp->mstrmap->stringvalue = oldtext.ToString();
			tempstringp->TextAssetEditor->TextAsset->stringmap.FindOrAdd(tempstringp->mstrmap->key) = oldtext.ToString();
			tempstringp->TextAssetEditor->TextAsset->MarkPackageDirty();
			tempstringp->StringvalueWidget->SetText(oldtext);
		}
		else if (std::is_same<TemplateType, float>::value)
		{
			Stemplatewidget<float>* tempstringp = (Stemplatewidget<float>*)mtemplatewidget;
			tempstringp->mstrmap->floatvalue = oldfloat;
			tempstringp->TextAssetEditor->TextAsset->floatmap.FindOrAdd(tempstringp->mstrmap->key) = oldfloat;
			tempstringp->TextAssetEditor->TextAsset->MarkPackageDirty();
			tempstringp->floatvalueWidget->SetValue(oldfloat);
		}
		else if (std::is_same<TemplateType, FVector>::value)
		{
			Stemplatewidget<FVector>* tempstringp = (Stemplatewidget<FVector>*)mtemplatewidget;
			tempstringp->mstrmap->vectorvalue = oldvector;
			tempstringp->TextAssetEditor->TextAsset->vectormap.FindOrAdd(tempstringp->mstrmap->key) = oldvector;
			tempstringp->TextAssetEditor->TextAsset->MarkPackageDirty();
			tempstringp->vectorvalueWidget->SetValue(oldvector);
		}
		else if (std::is_same<TemplateType, UObject*>::value)
		{
			Stemplatewidget<UObject*>* tempstringp = (Stemplatewidget<UObject*>*)mtemplatewidget;
			tempstringp->mstrmap->assetvalue = oldObject;
			tempstringp->TextAssetEditor->TextAsset->assetmap.FindOrAdd(tempstringp->mstrmap->key) = oldObject;
			tempstringp->TextAssetEditor->TextAsset->MarkPackageDirty();
			tempstringp->assetvalueWidget->SetAsset(oldObject);

		}
	}
};
template<typename TemplateType>
class rowAddRNdo :public RedoUndointerface
{
public:
	void* mtemplatewidget;
	TSharedPtr<str_value> mstrmap;
	void Redo() {
		if (std::is_same<TemplateType, FString>::value)
		{
			SKeyValueListWidget<FString>* tempstringp = (SKeyValueListWidget<FString>*)mtemplatewidget;
			tempstringp->Items.Add(mstrmap);//when add RequestListRefresh is  necessary
            //Update the listview
			tempstringp->ListViewWidget->RequestListRefresh();
			tempstringp->TextAssetEditor->TextAsset->stringmap.FindOrAdd(mstrmap->key) = mstrmap->stringvalue;
			tempstringp->TextAssetEditor->TextAsset->MarkPackageDirty();
		}
		if (std::is_same<TemplateType, float>::value)
		{
			SKeyValueListWidget<float>* tempstringp = (SKeyValueListWidget<float>*)mtemplatewidget;
			tempstringp->Items.Add(mstrmap);//when add RequestListRefresh is  necessary
			//Update the listview
			tempstringp->ListViewWidget->RequestListRefresh();
			tempstringp->TextAssetEditor->TextAsset->floatmap.FindOrAdd(mstrmap->key) = mstrmap->floatvalue;
			tempstringp->TextAssetEditor->TextAsset->MarkPackageDirty();
		}
		if (std::is_same<TemplateType, FVector>::value)
		{
			SKeyValueListWidget<FVector>* tempstringp = (SKeyValueListWidget<FVector>*)mtemplatewidget;
			tempstringp->Items.Add(mstrmap);//when add RequestListRefresh is  necessary
			//Update the listview
			tempstringp->ListViewWidget->RequestListRefresh();
			tempstringp->TextAssetEditor->TextAsset->vectormap.FindOrAdd(mstrmap->key) = mstrmap->vectorvalue;
			tempstringp->TextAssetEditor->TextAsset->MarkPackageDirty();
		}
		if (std::is_same<TemplateType, UObject*>::value)
		{
			SKeyValueListWidget<UObject*>* tempstringp = (SKeyValueListWidget<UObject*>*)mtemplatewidget;
			tempstringp->Items.Add(mstrmap);//when add RequestListRefresh is  necessary
			//Update the listview
			tempstringp->ListViewWidget->RequestListRefresh();
			tempstringp->TextAssetEditor->TextAsset->assetmap.FindOrAdd(mstrmap->key) = mstrmap->assetvalue.GetAsset();
			tempstringp->TextAssetEditor->TextAsset->MarkPackageDirty();
		}
	}
	void Undo() {
		//mStringMapListWidget->TextAssetEditor->TextAsset->stringmap.Remove(mstrmap->key);
		//mStringMapListWidget->Items.Remove(mstrmap);//when remove RequestListRefresh is not necessary
		//mStringMapListWidget->TextAssetEditor->TextAsset->MarkPackageDirty();
		if (std::is_same<TemplateType, FString>::value)
		{
			SKeyValueListWidget<FString>* tempstringp = (SKeyValueListWidget<FString>*)mtemplatewidget;
			tempstringp->TextAssetEditor->TextAsset->stringmap.Remove(mstrmap->key);
			tempstringp->Items.Remove(mstrmap);//when remove RequestListRefresh is not necessary
			tempstringp->TextAssetEditor->TextAsset->MarkPackageDirty();
		}
		if (std::is_same<TemplateType, float>::value)
		{
			SKeyValueListWidget<float>* tempstringp = (SKeyValueListWidget<float>*)mtemplatewidget;
			tempstringp->TextAssetEditor->TextAsset->floatmap.Remove(mstrmap->key);
			tempstringp->Items.Remove(mstrmap);//when remove RequestListRefresh is not necessary
			tempstringp->TextAssetEditor->TextAsset->MarkPackageDirty();
		}
		if (std::is_same<TemplateType, FVector>::value)
		{
			SKeyValueListWidget<FVector>* tempstringp = (SKeyValueListWidget<FVector>*)mtemplatewidget;
			tempstringp->TextAssetEditor->TextAsset->vectormap.Remove(mstrmap->key);
			tempstringp->Items.Remove(mstrmap);//when remove RequestListRefresh is not necessary
			tempstringp->TextAssetEditor->TextAsset->MarkPackageDirty();
		}
		if (std::is_same<TemplateType, UObject*>::value)
		{
			SKeyValueListWidget<UObject*>* tempstringp = (SKeyValueListWidget<UObject*>*)mtemplatewidget;
			tempstringp->TextAssetEditor->TextAsset->assetmap.Remove(mstrmap->key);
			tempstringp->Items.Remove(mstrmap);//when remove RequestListRefresh is not necessary
			tempstringp->TextAssetEditor->TextAsset->MarkPackageDirty();
		}
	}
};
template<typename TemplateType>
class rowDeleteRNdo :public RedoUndointerface
{


public:
	void* mtemplatewidget;
	TSharedPtr<str_value> mstrmap;
	void Redo() {
		if (std::is_same<TemplateType, FString>::value)
		{
			SKeyValueListWidget<FString>* tempstringp = (SKeyValueListWidget<FString>*)mtemplatewidget;
			tempstringp->TextAssetEditor->TextAsset->stringmap.Remove(mstrmap->key);
			tempstringp->Items.Remove(mstrmap);//when remove RequestListRefresh is not necessary
			tempstringp->TextAssetEditor->TextAsset->MarkPackageDirty();
		}
		if (std::is_same<TemplateType, float>::value)
		{
			SKeyValueListWidget<float>* tempstringp = (SKeyValueListWidget<float>*)mtemplatewidget;
			tempstringp->TextAssetEditor->TextAsset->floatmap.Remove(mstrmap->key);
			tempstringp->Items.Remove(mstrmap);//when remove RequestListRefresh is not necessary
			tempstringp->TextAssetEditor->TextAsset->MarkPackageDirty();
		}
		if (std::is_same<TemplateType, FVector>::value)
		{
			SKeyValueListWidget<FVector>* tempstringp = (SKeyValueListWidget<FVector>*)mtemplatewidget;
			tempstringp->TextAssetEditor->TextAsset->vectormap.Remove(mstrmap->key);
			tempstringp->Items.Remove(mstrmap);//when remove RequestListRefresh is not necessary
			tempstringp->TextAssetEditor->TextAsset->MarkPackageDirty();
		}
		if (std::is_same<TemplateType, UObject*>::value)
		{
			SKeyValueListWidget<UObject*>* tempstringp = (SKeyValueListWidget<UObject*>*)mtemplatewidget;
			tempstringp->TextAssetEditor->TextAsset->assetmap.Remove(mstrmap->key);
			tempstringp->Items.Remove(mstrmap);//when remove RequestListRefresh is not necessary
			tempstringp->TextAssetEditor->TextAsset->MarkPackageDirty();
		}
	}
	void Undo() {
		if (std::is_same<TemplateType, FString>::value)
		{
			SKeyValueListWidget<FString>* tempstringp = (SKeyValueListWidget<FString>*)mtemplatewidget;	
			tempstringp->Items.Add(mstrmap);//when add RequestListRefresh is  necessary
             //Update the listview
			tempstringp->ListViewWidget->RequestListRefresh();
			tempstringp->TextAssetEditor->TextAsset->stringmap.FindOrAdd(mstrmap->key) = mstrmap->stringvalue;
			tempstringp->TextAssetEditor->TextAsset->MarkPackageDirty();
		}
		if (std::is_same<TemplateType, float>::value)
		{
			SKeyValueListWidget<float>* tempstringp = (SKeyValueListWidget<float>*)mtemplatewidget;
			tempstringp->Items.Add(mstrmap);//when add RequestListRefresh is  necessary
			 //Update the listview
			tempstringp->ListViewWidget->RequestListRefresh();
			tempstringp->TextAssetEditor->TextAsset->floatmap.FindOrAdd(mstrmap->key) = mstrmap->floatvalue;
			tempstringp->TextAssetEditor->TextAsset->MarkPackageDirty();
		}
		if (std::is_same<TemplateType, FVector>::value)
		{
			SKeyValueListWidget<FVector>* tempstringp = (SKeyValueListWidget<FVector>*)mtemplatewidget;
			tempstringp->Items.Add(mstrmap);//when add RequestListRefresh is  necessary
		 //Update the listview
			tempstringp->ListViewWidget->RequestListRefresh();
			tempstringp->TextAssetEditor->TextAsset->vectormap.FindOrAdd(mstrmap->key) = mstrmap->vectorvalue;
			tempstringp->TextAssetEditor->TextAsset->MarkPackageDirty();
		}
		if (std::is_same<TemplateType, UObject*>::value)
		{
			SKeyValueListWidget<UObject*>* tempstringp = (SKeyValueListWidget<UObject*>*)mtemplatewidget;
			tempstringp->Items.Add(mstrmap);//when add RequestListRefresh is  necessary
			 //Update the listview
			tempstringp->ListViewWidget->RequestListRefresh();
			tempstringp->TextAssetEditor->TextAsset->assetmap.FindOrAdd(mstrmap->key) = mstrmap->assetvalue.GetAsset();
			tempstringp->TextAssetEditor->TextAsset->MarkPackageDirty();
		}
	}
};
template<typename TemplateType>
class  SKeyValueListWidget : public SCompoundWidget,public Ikeyvlaueinterface
{
	bool bvisibilitytest = true;
	TSharedPtr<STextBlock> titlewidget;
public:
	virtual ~SKeyValueListWidget() {}
	SLATE_BEGIN_ARGS(SKeyValueListWidget<TemplateType>)
	{}
	SLATE_END_ARGS()
		FString title = "";
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
				SAssignNew(titlewidget,STextBlock)
				.TextStyle(FEditorStyle::Get(), "ContentBrowser.TopBar.Font")
				.Text(FText::FromString("title"))
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
						TSharedPtr<str_value> tempstr_value = MakeShareable(new str_value());
						tempstr_value->b_canrndo = true;
						Items.Add(tempstr_value);//when add RequestListRefresh is  necessary
						//Update the listview
						ListViewWidget->RequestListRefresh();
						///////////////////////////////////////////////////////////////////////////////////////////////////////
							rowAddRNdo<TemplateType>* rrndop = new rowAddRNdo<TemplateType>();
							rrndop->mtemplatewidget = this;
							rrndop->mstrmap = tempstr_value;
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
			SAssignNew(ListViewWidget, SListView<TSharedPtr<str_value>>)
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
            .OnGenerateRow(this, &SKeyValueListWidget<TemplateType>::OnGenerateRowForList)
		]
		];
		initialize();
	}
	void initialize()
	{
		if (std::is_same<TemplateType, FString>::value)
		{
			titlewidget->SetText(FText::FromString("string map"));
			for (TMap<FString, FString>::TIterator it = TextAsset->stringmap.CreateIterator(); it; ++it)
			{
				TSharedPtr<str_value> temp = MakeShareable(new str_value());
				temp->key = it->Key;
				temp->stringvalue = it->Value;
				temp->b_canrndo = false;
				Items.Add(temp);
			}
		}
		else if (std::is_same<TemplateType, float>::value)
		{
			titlewidget->SetText(FText::FromString("float map"));
			for (TMap<FString, float>::TIterator it = TextAsset->floatmap.CreateIterator(); it; ++it)
			{
				TSharedPtr<str_value> temp = MakeShareable(new str_value());
				temp->key = it->Key;
				temp->floatvalue = it->Value;
				temp->b_canrndo = false;
				Items.Add(temp);
			}
		}
		else if (std::is_same<TemplateType, FVector>::value)
		{
			titlewidget->SetText(FText::FromString("vector map"));
			for (TMap<FString, FVector>::TIterator it = TextAsset->vectormap.CreateIterator(); it; ++it)
			{
				TSharedPtr<str_value> temp = MakeShareable(new str_value());
				temp->key = it->Key;
				temp->vectorvalue = it->Value;
				temp->b_canrndo = false;
				Items.Add(temp);
			}
		}
		else if (std::is_same<TemplateType, UObject*>::value)
		{
			titlewidget->SetText(FText::FromString("object map"));
			for (TMap<FString, UObject*>::TIterator it = TextAsset->assetmap.CreateIterator(); it; ++it)
			{
				TSharedPtr<str_value> temp = MakeShareable(new str_value());
				temp->key = it->Key;
				temp->assetvalue = it->Value;
				temp->b_canrndo = false;
				Items.Add(temp);
			}
		}
	}
	virtual void Onkeyvaluelistdeleterow(TSharedPtr<str_value> pstr_str) override
	{
		if (std::is_same<TemplateType, FString>::value)
		{
			TextAssetEditor->TextAsset->stringmap.Remove(pstr_str->key);
			Items.Remove(pstr_str);//when remove RequestListRefresh is not necessary
			TextAssetEditor->TextAsset->MarkPackageDirty();
		}
		if (std::is_same<TemplateType, float>::value)
		{
			TextAssetEditor->TextAsset->floatmap.Remove(pstr_str->key);
			Items.Remove(pstr_str);//when remove RequestListRefresh is not necessary
			TextAssetEditor->TextAsset->MarkPackageDirty();
		}
		if (std::is_same<TemplateType, FVector>::value)
		{
			TextAssetEditor->TextAsset->vectormap.Remove(pstr_str->key);
			Items.Remove(pstr_str);//when remove RequestListRefresh is not necessary
			TextAssetEditor->TextAsset->MarkPackageDirty();
		}
		if (std::is_same<TemplateType, UObject*>::value)
		{
			TextAssetEditor->TextAsset->assetmap.Remove(pstr_str->key);
			Items.Remove(pstr_str);//when remove RequestListRefresh is not necessary
			TextAssetEditor->TextAsset->MarkPackageDirty();
		}
		////////////////////////////////////////////////////////////////////////////
		rowDeleteRNdo<TemplateType>* rdrp = new rowDeleteRNdo<TemplateType>();
		rdrp->mtemplatewidget = this;
		rdrp->mstrmap = pstr_str;
		pstr_str->b_canrndo = true;
		TextAssetEditor->TexAssetEditorRedoUndoManager->Undostack->Push(rdrp);
	}
	TSharedRef<ITableRow> OnGenerateRowForList(TSharedPtr<str_value> Item, const TSharedRef<STableViewBase>& OwnerTable) {
		TSharedPtr<Stemplatewidget<TemplateType>> TabWidget = SNew(Stemplatewidget<TemplateType>, Item, TextAssetEditor, this);
		//TSharedPtr<SButton> TabWidget = SNew(SButton);
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
	TArray<TSharedPtr<str_value>> Items;

	/* The actual UI list */
	TSharedPtr<SListView<TSharedPtr<str_value>>> ListViewWidget;
};

