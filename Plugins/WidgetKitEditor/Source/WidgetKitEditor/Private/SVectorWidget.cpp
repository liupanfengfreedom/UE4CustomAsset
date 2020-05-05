// Fill out your copyright notice in the Description page of Project Settings.


#include "SVectorWidget.h"
#include "SlateOptMacros.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Input/SSpinBox.h"
BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SVectorWidget::Construct(const FArguments& InArgs)
{
	
	ChildSlot
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		[
			SNew(STextBlock)
			.Text(FText::FromString("X:"))
		]
	   + SHorizontalBox::Slot()
		.AutoWidth()
		[ 
			SNew(SBox)
			.MinDesiredHeight(20)
		   .MinDesiredWidth(100)
		   [
			   SAssignNew(xwidget,SSpinBox<float>)
			   .Value(InArgs._X)
			   .OnValueCommitted_Lambda([this](float v, ETextCommit::Type type) {
				   bool b_canbecalled = OncommittedX.IsBound();
				   if (b_canbecalled)
				   {
					   OncommittedX.Execute(v);
				   }
				})
		   ]
		]
	   + SHorizontalBox::Slot()
		   .AutoWidth()
		   [
			   SNew(STextBlock)
			   .Text(FText::FromString("Y:"))
		   ]
	   + SHorizontalBox::Slot()
		   .AutoWidth()
		   [
			   SNew(SBox)
			   .MinDesiredHeight(20)
		   .MinDesiredWidth(100)
		   [
			   SAssignNew(ywidget, SSpinBox<float>)
			   .Value(InArgs._Y)
			   .OnValueCommitted_Lambda([this](float v, ETextCommit::Type type) {
			   bool b_canbecalled = OncommittedY.IsBound();
			   if (b_canbecalled)
			   {
				   OncommittedY.Execute(v);
			   }
				})
		   ]
		   ]
	   + SHorizontalBox::Slot()
		   .AutoWidth()
		   [
			   SNew(STextBlock)
			   .Text(FText::FromString("Z:"))
		   ]
	   + SHorizontalBox::Slot()
		   .AutoWidth()
		   [
			   SNew(SBox)
			   .MinDesiredHeight(20)
		   .MinDesiredWidth(100)
		   [
			   SAssignNew(zwidget, SSpinBox<float>)
			   .Value(InArgs._Z)
			   .OnValueCommitted_Lambda([this](float v, ETextCommit::Type type) {
			   bool b_canbecalled = OncommittedZ.IsBound();
			   if (b_canbecalled)
			   {
				   OncommittedZ.Execute(v);
			   }
				   })
		   ]
		   ]
	];
	OncommittedX = InArgs._OncommittedX;
	OncommittedY = InArgs._OncommittedY;
	OncommittedZ = InArgs._OncommittedZ;
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SVectorWidget::SetValue(FVector value)
{
	xwidget->SetValue(value.X);
	ywidget->SetValue(value.Y);
	zwidget->SetValue(value.Z);
}