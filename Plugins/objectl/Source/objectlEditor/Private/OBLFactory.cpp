// Fill out your copyright notice in the Description page of Project Settings.


#include "OBLFactory.h"
#include "MyObject.h"

UOBLFactory::UOBLFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SupportedClass = UMyObject::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}


/* UFactory overrides
 *****************************************************************************/

UObject* UOBLFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UMyObject>(InParent, InClass, InName, Flags);
}


bool UOBLFactory::ShouldShowInNewMenu() const
{
	return true;
}