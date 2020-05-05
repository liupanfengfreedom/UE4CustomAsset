// Fill out your copyright notice in the Description page of Project Settings.


#include "SToolbarWidget.h"
#include "SlateOptMacros.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/SBoxPanel.h"
#include "EditorStyle.h"
BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SToolbarWidget::Construct(const FArguments& InArgs, STextAssetEditor* InTextAssetEditor)
{
	TextAssetEditor = InTextAssetEditor;
	ChildSlot
	[
		SNew(SHorizontalBox)

		// Button (only image)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(2)
		[
			SAssignNew(undobutton,SButton)
			.IsEnabled(false)
			.ButtonStyle(FEditorStyle::Get(), "FlatButton")
			.ToolTipText(FText::FromString("Undo"))
			.ContentPadding(FMargin(4, 5, 3, 0))
			.OnClicked_Lambda([=]() {
		         void* rni=nullptr;
		         TextAssetEditor->TexAssetEditorRedoUndoManager->Undostack->Pop(rni);
				 TextAssetEditor->TexAssetEditorRedoUndoManager->Redostack->Push(rni);
				 ((RedoUndointerface*)rni)->Undo();
		      return FReply::Handled();
			})
		    [
				SNew(STextBlock)
				.TextStyle(FEditorStyle::Get(), "ContentBrowser.TopBar.Font")
				.Font(FEditorStyle::Get().GetFontStyle("FontAwesome.14"))
				.Text(FEditorFontGlyphs::Undo)
		    ]
		]

	// Button (only image)
	+ SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(2)
		[
			SAssignNew(redobutton, SButton)
			.IsEnabled(false)
		    .ButtonStyle(FEditorStyle::Get(), "FlatButton")
			.ToolTipText(FText::FromString("Redo"))
			.ContentPadding(FMargin(4, 5, 3, 0))
			.OnClicked_Lambda([=]() {
				void* rni = nullptr;
				TextAssetEditor->TexAssetEditorRedoUndoManager->Redostack->Pop(rni);
				TextAssetEditor->TexAssetEditorRedoUndoManager->Undostack->Push(rni);
				((RedoUndointerface*)rni)->Redo();
			     return FReply::Handled();
				})
		[
			SNew(STextBlock)
			.TextStyle(FEditorStyle::Get(), "ContentBrowser.TopBar.Font")
			.Font(FEditorStyle::Get().GetFontStyle("FontAwesome.12"))
			.Text(FEditorFontGlyphs::Repeat)
		]
		]
	];
	TextAssetEditor->TexAssetEditorRedoUndoManager->Undostack->Stackemptyevent.BindLambda([=]() {
		    undobutton->SetEnabled(false);
		});
	TextAssetEditor->TexAssetEditorRedoUndoManager->Undostack->Stacknotemptyevent.BindLambda([=]() {
		    undobutton->SetEnabled(true);
		});

	TextAssetEditor->TexAssetEditorRedoUndoManager->Redostack->Stackemptyevent.BindLambda([=]() {
		    redobutton->SetEnabled(false);
		});
	TextAssetEditor->TexAssetEditorRedoUndoManager->Redostack->Stacknotemptyevent.BindLambda([=]() {
		    redobutton->SetEnabled(true);
		});
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
