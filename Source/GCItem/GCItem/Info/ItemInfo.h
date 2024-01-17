// Copyright (C) 2024 owoDra

#pragma once

#include "ItemInfo.generated.h"


/**
 * Base class for item information concepts
 */
UCLASS(Abstract, Const, DefaultToInstanced, EditInlineNew)
class GCITEM_API UItemInfo : public UObject
{
	GENERATED_BODY()
public:
	UItemInfo(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

};
