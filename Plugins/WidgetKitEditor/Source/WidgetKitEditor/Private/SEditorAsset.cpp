// Fill out your copyright notice in the Description page of Project Settings.


#include "SEditorAsset.h"
#include "SlateOptMacros.h"
#include "Widgets/SBoxPanel.h"
#include "SAssetDropTarget.h"
#include "Widgets/Input/SComboButton.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "EditorStyleSet.h"
#include "Widgets/Images/SImage.h"
#include "Editor.h"
#include "Engine/Selection.h"
#include "AssetThumbnail.h"
#include "PropertyCustomizationHelpers.h"
#include "AssetThumbnail.h"
#include "Modules/ModuleManager.h"
#include "AssetToolsModule.h"
#include "Widgets/Input/SButton.h"
//#include "Editor/PropertyEditor/Private/UserInterface/PropertyEditor/SPropertyEditorAsset.h"
BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SEditorAsset::Construct(const FArguments& InArgs)
{
	AssetComboButton = SNew(SComboButton)
		.ToolTipText(FText::FromString("combobutton tooltiptext"))
		.ButtonStyle(FEditorStyle::Get(), "PropertyEditor.AssetComboStyle")
		.ForegroundColor(FEditorStyle::GetColor("PropertyEditor.AssetName.ColorAndOpacity"))
		.OnGetMenuContent_Lambda([this]()->TSharedRef<SWidget> {
			FAssetData AssetData;
			TArray<const UClass*> DisallowedClassFilters;
			/** A list of the factories we can use to create new assets */
			TArray<UFactory*> NewAssetFactories;
			return PropertyCustomizationHelpers::MakeAssetPickerWithMenu(AssetData,
				true,
				true,
				DisallowedClassFilters,
				NewAssetFactories,
				nullptr,
				FOnAssetSelected::CreateSP(this, &SEditorAsset::OnAssetSelected),
				FSimpleDelegate::CreateSP(this, &SEditorAsset::CloseComboButton),
				nullptr,
				OwnerAssetDataArray);
			})
		.OnMenuOpenChanged_Lambda([this](bool bOpen) {
				if (bOpen == false)
				{
					AssetComboButton->SetMenuContent(SNullWidget::NullWidget);
				}
			})
				.IsEnabled(true)
				.ContentPadding(2.0f)
				.ButtonContent()
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.HAlign(HAlign_Left)
					.VAlign(VAlign_Center)
					[
						SNew(STextBlock)
						.MinDesiredWidth(60)
						.Text_Lambda([this]()->FText {
							  return FText::FromName(mAssetdata.AssetName);
						})
					]

				];
			FAssetThumbnailConfig AssetThumbnailConfig;
			//TSharedPtr<IAssetTypeActions> AssetTypeActions;
			//FAssetToolsModule& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>(TEXT("AssetTools"));
			//AssetTypeActions = AssetToolsModule.Get().GetAssetTypeActionsForClass(UStaticMesh::StaticClass()).Pin();
			//if (AssetTypeActions.IsValid())
			//{
			//	AssetThumbnailConfig.ClassThumbnailBrushOverride =  FName("None");
			//}
			TSharedRef<FAssetThumbnailPool> ThumbnailPoolref = MakeShared<FAssetThumbnailPool>(1, false);
			AssetThumbnail = MakeShareable(new FAssetThumbnail(mAssetdata, 60, 60, ThumbnailPoolref));
			TSharedPtr<SHorizontalBox> ValueContentBox = nullptr;
			ChildSlot
				[
					SNew(SAssetDropTarget)
					.OnIsAssetAcceptableForDrop_Lambda([this](const UObject* InObject) {
				          return true;
					})
					.OnAssetDropped_Lambda([this](const UObject* InObject) {
								//mAssetdata = InObject;//amazing!
								SetAsset(InObject);
						})
					[
						SAssignNew(ValueContentBox, SHorizontalBox)
					]
				];

			ValueContentBox->AddSlot()
				.Padding(0.0f, 0.0f, 2.0f, 0.0f)
				.AutoWidth()
				.VAlign(VAlign_Center)
				[
					SAssignNew(ThumbnailBorder, SBorder)
					.Padding(5.0f)
				.BorderImage_Lambda([this]() {
				if (ThumbnailBorder->IsHovered())
				{
					return FEditorStyle::GetBrush("PropertyEditor.AssetThumbnailLight");
				}
				else
				{
					return FEditorStyle::GetBrush("PropertyEditor.AssetThumbnailShadow");
				}
					})
				.OnMouseDoubleClick_Lambda([this](const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) {
						OnOpenAssetEditor();
						return FReply::Handled();
					})
				[
						SNew(SBox)
							//.ToolTipText(TooltipAttribute)
						.WidthOverride(60)
						.HeightOverride(60)
						[
							AssetThumbnail->MakeThumbnailWidget(AssetThumbnailConfig)
						]
				]
				];
			TSharedRef<SHorizontalBox> ButtonBox = SNew(SHorizontalBox);

			ValueContentBox->AddSlot()
				.Padding(0.0f, 0.0f, 0.0f, 0.0f)
				.AutoWidth()
				.VAlign(VAlign_Center)
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					.Padding(1.0f, -1.0f, 1.0f, 5.0f)
					.HAlign(HAlign_Left)
					.VAlign(VAlign_Top)
					[
						AssetComboButton.ToSharedRef()
					]
				    + SVerticalBox::Slot()
					.HAlign(HAlign_Left)
					.VAlign(VAlign_Top)
					[
						ButtonBox
				    ]
				];
			ButtonBox->AddSlot()
				.VAlign(VAlign_Center)
				.AutoWidth()
				.Padding(2.0f, 0.0f)
				[
					PropertyCustomizationHelpers::MakeUseSelectedButton(FSimpleDelegate::CreateSP(this, &SEditorAsset::OnUse), FText(), true)
				];
			ButtonBox->AddSlot()
				.VAlign(VAlign_Center)
				.AutoWidth()
				.Padding(2.0f, 0.0f)
				[
					PropertyCustomizationHelpers::MakeBrowseButton(
						FSimpleDelegate::CreateSP(this, &SEditorAsset::OnBrowse),
						TAttribute<FText>(this, &SEditorAsset::GetOnBrowseToolTip)
					)
		        ];
			ButtonBox->AddSlot()
				.Padding(4.0f, 0.0f)
				.AutoWidth()
				.VAlign(VAlign_Center)
				[
					SNew(SButton)
					.ButtonStyle(FEditorStyle::Get(), "FlatButton")
				    .OnClicked_Lambda([this]() {
				        SetAsset(nullptr);
				        return FReply::Handled();

					})
					[
						SNew(SImage)
				        .Image(FEditorStyle::GetBrush("PropertyWindow.DiffersFromDefault"))
					]
				];

			SetAsset(InArgs._argAssetdata.Get());
			Oncommitted = InArgs._Oncommitted;
}
void SEditorAsset::OnOpenAssetEditor()
{
	UObject* ObjectToEdit = mAssetdata.GetAsset();
	if (ObjectToEdit)
	{
		GEditor->EditObject(ObjectToEdit);
	}
}
void SEditorAsset::OnAssetSelected(const struct FAssetData& AssetData)
{
	SetAsset(AssetData);
}

void SEditorAsset::CloseComboButton()
{
	AssetComboButton->SetIsOpen(false);
}
void SEditorAsset::SetAsset(const FAssetData& passet) {
	mAssetdata = passet;
	AssetThumbnail->SetAsset(mAssetdata);
	bool b_canbecalled = Oncommitted.IsBound();
	if (b_canbecalled)
	{
		Oncommitted.Execute(passet);
	}
}
void SEditorAsset::OnUse()
{
	FEditorDelegates::LoadSelectedAssetsIfNeeded.Broadcast();
	UObject* Selection = nullptr;
	UClass* objectclass = UObject::StaticClass();
	Selection = GEditor->GetSelectedObjects()->GetTop(objectclass);
	if (Selection)
	{
		SetAsset(Selection);
	}
}
void SEditorAsset::OnBrowse()
{
	TArray<FAssetData> AssetDataList;
	AssetDataList.Add(mAssetdata);
	GEditor->SyncBrowserToObjects(AssetDataList);
}

FText SEditorAsset::GetOnBrowseToolTip()const
{
	return FText::FromString("BrowseToAssetInContentBrowser Browse to Asset in Content Browser");
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
