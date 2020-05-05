// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "STextAssetEditor.h"

#include "Fonts/SlateFontInfo.h"
#include "Internationalization/Text.h"
#include "TextAsset.h"
#include "UObject/Class.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Input/SButton.h"

#include "Slate/Public/Widgets/Input/SNumericEntryBox.h"
#include "SlateFwd.h"
#include "Slate/Public/Widgets/Input/SRotatorInputBox.h"
#include "Slate/Public/Widgets/Input/SSpinBox.h"
#include "SToolbarWidget.h"

#include "Engine.h"
#include "SEditorAsset.h"
#include "SStringMapListWidget.h"
#include "SAssetMapListWidget.h"


#include "TextAssetEditorSettings.h"
#include "RedoUndoStack.h"
#include "Stemplatewidget.h"



#define LOCTEXT_NAMESPACE "STextAssetEditor"
//#define TT1	

/* STextAssetEditor interface
 *****************************************************************************/
STextAssetEditor::~STextAssetEditor()
{
	FCoreUObjectDelegates::OnObjectPropertyChanged.RemoveAll(this);
}


void STextAssetEditor::Construct(const FArguments& InArgs, UTextAsset* InTextAsset, const TSharedRef<ISlateStyle>& InStyle)
{
	TexAssetEditorRedoUndoManager = MakeShareable(new RedoUndoManager());

	TextAsset = InTextAsset;

	auto Settings = GetDefault<UTextAssetEditorSettings>();
	TSharedPtr<SHorizontalBox> ValueContentBox = nullptr;


	ChildSlot
	[
#ifdef TT1
		SNew(SVerticalBox)

		+ SVerticalBox::Slot()
		.AutoHeight()
		//.FillHeight(0.3f)
			[
				SNew(SToolbarWidget,this)
			]
	+ SVerticalBox::Slot()
		//.AutoHeight()
		.FillHeight(1.0f)
		[
			SNew(SScrollBox)
			+ SScrollBox::Slot()
			[
				SNew(SButton)
				.Text(LOCTEXT("Add_string","Add new list item"))
		        .OnClicked_Lambda([this]() {
						Items.Add(MakeShareable(new FString("Hello 1")));
						//Update the listview
						ListViewWidget->RequestListRefresh();
						return FReply::Handled();
					})
			]
	         //The actual list view creation
		    + SScrollBox::Slot()
			[
				SAssignNew(ListViewWidget, SListView<TSharedPtr<FString>>)
				.ItemHeight(24)
			    .ListItemsSource(&Items) //The Items array is the source of this listview
			    .OnGenerateRow(this, &STextAssetEditor::OnGenerateRowForList)
			]
		]
	+ SVerticalBox::Slot()
		//.AutoHeight()
		.FillHeight(1.0f)
		[
			SNew(SStringlist)
			.Text1(FText::FromString("hi this is a test1"))
			.Text2(FText::FromString("hi this is a test2"))
			.OnClicked_Lambda([=]() {
		        f1();
				return FReply::Handled();
				})
		    .OnHovered_Lambda([=]() {
				f2();
			})
			
		]
	+ SVerticalBox::Slot()
		//.AutoHeight()
		.FillHeight(1.0f)
		[
			SAssignNew(Stringmap_list, SStringMapListWidget, this)
		]
	+ SVerticalBox::Slot()
		//.AutoHeight()
		.FillHeight(1.0f)
		[
			//SAssignNew(PrimaryWidget, SNumericEntryBox<float>)
			SNew(SSpinBox<float>)
		    .OnValueCommitted_Lambda([=](float v, ETextCommit::Type type) {
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("OnValueCommitted_Lambda"));

				})
		    //Only allow spinning if we have a single value
			//.AllowSpin(bAllowSpin)
			//.Value(this, &SPropertyEditorNumeric<NumericType>::OnGetValue)
			//.Font(InArgs._Font)
			//.MinValue(MinValue)
			//.MaxValue(MaxValue)
			//.MinSliderValue(SliderMinValue)
			//.MaxSliderValue(SliderMaxValue)
			//.SliderExponent(SliderExponent)
			//.Delta(Delta)
			//.UndeterminedString(LOCTEXT("MultipleValues", "Multiple Values"))
			//.OnValueChanged(this, &SPropertyEditorNumeric<NumericType>::OnValueChanged)
			//.OnValueCommitted(this, &SPropertyEditorNumeric<NumericType>::OnValueCommitted)
			//.OnUndeterminedValueCommitted(this, &SPropertyEditorNumeric<NumericType>::OnUndeterminedValueCommitted)
			//.OnBeginSliderMovement(this, &SPropertyEditorNumeric<NumericType>::OnBeginSliderMovement)
			//.OnEndSliderMovement(this, &SPropertyEditorNumeric<NumericType>::OnEndSliderMovement)
			//.TypeInterface(TypeInterface)
		]
	+ SVerticalBox::Slot()
		//.AutoHeight()
		.FillHeight(1.0f)
		[
			//SAssignNew(PrimaryWidget, SNumericEntryBox<float>)
			//SNew(SSpinBox<int>)
			SNew(SEditorAsset)
			//Only allow spinning if we have a single value
			//.AllowSpin(bAllowSpin)
			//.Value(this, &SPropertyEditorNumeric<NumericType>::OnGetValue)
			//.Font(InArgs._Font)
			//.MinValue(MinValue)
			//.MaxValue(MaxValue)
			//.MinSliderValue(SliderMinValue)
			//.MaxSliderValue(SliderMaxValue)
			//.SliderExponent(SliderExponent)
			//.Delta(Delta)
			//.UndeterminedString(LOCTEXT("MultipleValues", "Multiple Values"))
			//.OnValueChanged(this, &SPropertyEditorNumeric<NumericType>::OnValueChanged)
			//.OnValueCommitted(this, &SPropertyEditorNumeric<NumericType>::OnValueCommitted)
			//.OnUndeterminedValueCommitted(this, &SPropertyEditorNumeric<NumericType>::OnUndeterminedValueCommitted)
			//.OnBeginSliderMovement(this, &SPropertyEditorNumeric<NumericType>::OnBeginSliderMovement)
			//.OnEndSliderMovement(this, &SPropertyEditorNumeric<NumericType>::OnEndSliderMovement)
			//.TypeInterface(TypeInterface)
		]
#else

		SNew(SScrollBox)
		+ SScrollBox::Slot()
		[
			SNew(SToolbarWidget, this)
		]
		//+ SScrollBox::Slot()
		//[
		//	//SAssignNew(Assetgmap_list, SAssetMapListWidget, this)
		//	SNew(SAssetMapListWidget, this)
		//]
		//+ SScrollBox::Slot()
		//[
		//	SNew(SStringMapListWidget, this)
		//	//SAssignNew(Stringmap_list, SStringMapListWidget, this)
		//]
		+ SScrollBox::Slot()
		[
			SNew(SKeyValueListWidget<float>,this)
		]
		+ SScrollBox::Slot()
		[
			SNew(SKeyValueListWidget<FString>, this)
		]
		+ SScrollBox::Slot()
		[
			SNew(SKeyValueListWidget<FVector>, this)
		]
		+ SScrollBox::Slot()
		[
			SNew(SKeyValueListWidget<UObject*>, this)
		]
#endif // TT1
	];

	FCoreUObjectDelegates::OnObjectPropertyChanged.AddSP(this, &STextAssetEditor::HandleTextAssetPropertyChanged);
}
const FSlateBrush* STextAssetEditor::GetThumbnailBorder()const
{
	return FEditorStyle::GetBrush("PropertyEditor.AssetThumbnailLight");
}
FReply STextAssetEditor::ButtonPressed()
{
	Items.Add(MakeShareable(new FString("Hello 1")));

	//Update the listview
	ListViewWidget->RequestListRefresh();
	return FReply::Handled();
}
TSharedRef<ITableRow> STextAssetEditor::OnGenerateRowForList(TSharedPtr<FString> Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	TSharedPtr<STextBlock> TabWidget = SNew(STextBlock);	
	TabWidget->SetText(*Item.Get());
	return
		SNew(STableRow< TSharedPtr<FString> >, OwnerTable)
		.Padding(2.0f)
		[
			TabWidget.ToSharedRef()
		];
}
/* STextAssetEditor callbacks
 *****************************************************************************/

void STextAssetEditor::HandleEditableTextBoxTextChanged(const FText& NewText)
{
	TextAsset->MarkPackageDirty();
}


void STextAssetEditor::HandleEditableTextBoxTextCommitted(const FText& Comment, ETextCommit::Type CommitType)
{
	TextAsset->Text = EditableTextBox->GetText();
}


void STextAssetEditor::HandleTextAssetPropertyChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent)
{
	if (Object == TextAsset)
	{
		EditableTextBox->SetText(TextAsset->Text);
	}
}
void STextAssetEditor::f1()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("f1() !"));
}
void STextAssetEditor::f2()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("f2() !"));
}
TOptional<float> STextAssetEditor::GetTransformDelta()const
{
	return SomeoneFloat;
}
void STextAssetEditor::TransformDeltaCommited(float newValue, ETextCommit::Type CommitType)
{
	SomeoneFloat = newValue;
}
#undef LOCTEXT_NAMESPACE
