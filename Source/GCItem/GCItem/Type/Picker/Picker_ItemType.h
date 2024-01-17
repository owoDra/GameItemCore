// Copyright (C) 2024 owoDra

#pragma once

#include "UObject/Object.h"

#include "Picker_ItemType.generated.h"


/**
 * Data for selecting a predefined ItemType
 * 
 * Tips:
 *  ItemType can be defined from DeveloperSetting.
 */
USTRUCT(BlueprintType)
struct GCITEM_API FPicker_ItemType
{
	GENERATED_BODY()

	static const FPicker_ItemType Empty;

public:
	FPicker_ItemType() {}
	FPicker_ItemType(FName InName) : Name(InName) {}

public:
	//
	// Name of ItemType
	//
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName Name{ NAME_None };

public:
	bool IsValid() const { return (Name.IsValid() && !Name.IsNone()); }

};


