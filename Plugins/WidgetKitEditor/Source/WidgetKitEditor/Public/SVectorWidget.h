// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Input/SSpinBox.h"

#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
DECLARE_DELEGATE_OneParam(FonEditorFloatCommitted, const float&)

class WIDGETKITEDITOR_API SVectorWidget : public SCompoundWidget
{
	TSharedPtr<SSpinBox<float>> xwidget;
	TSharedPtr<SSpinBox<float>> ywidget;
	TSharedPtr<SSpinBox<float>> zwidget;
public:
	SLATE_BEGIN_ARGS(SVectorWidget)
	{}
	    SLATE_ATTRIBUTE(float, X)
		SLATE_ATTRIBUTE(float, Y)
		SLATE_ATTRIBUTE(float, Z)
		SLATE_EVENT(FonEditorFloatCommitted, OncommittedX)
		SLATE_EVENT(FonEditorFloatCommitted, OncommittedY)
		SLATE_EVENT(FonEditorFloatCommitted, OncommittedZ)
	SLATE_END_ARGS()
	FonEditorFloatCommitted OncommittedX;
	FonEditorFloatCommitted OncommittedY;
	FonEditorFloatCommitted OncommittedZ;
	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	void SetValue(FVector value);
};
