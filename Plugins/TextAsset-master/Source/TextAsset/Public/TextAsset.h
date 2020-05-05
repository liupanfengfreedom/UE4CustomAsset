// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Internationalization/Text.h"
#include "UObject/Object.h"
#include "UObject/ObjectMacros.h"
#include "AssetData.h"
#include "TextAsset.generated.h"


/**
 * Implements an asset that can be used to store arbitrary text, such as notes
 * or documentation sky.
 */
UCLASS(BlueprintType, hidecategories=(Object))
class TEXTASSET_API UTextAsset
	: public UObject
{
	GENERATED_BODY()

public:

	/** Holds the stored text. */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="TextAsset")
	FText Text;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "TextAsset")
	TMap<FString, FString> stringmap;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "TextAsset")
	TMap<FString, UObject*> assetmap;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "TextAsset")
	TMap<FString, float> floatmap;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "TextAsset")
	TMap<FString, FVector> vectormap;
};
