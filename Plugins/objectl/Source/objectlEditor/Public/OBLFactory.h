// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "OBLFactory.generated.h"

/**
 * 
 */
UCLASS()
class OBJECTLEDITOR_API UOBLFactory : public UFactory
{
	GENERATED_BODY()
public:
	UOBLFactory(const FObjectInitializer& ObjectInitializer);
		virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	virtual bool ShouldShowInNewMenu() const override;
};
