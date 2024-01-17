// Copyright (C) 2024 owoDra

#include "ItemData.h"

#include "Info/ItemInfo.h"

#if WITH_EDITOR
#include "Misc/DataValidation.h"
#endif

#include UE_INLINE_GENERATED_CPP_BY_NAME(ItemData)

/////////////////////////////////////////////////////////////////////////////////////////////////////

const FName UItemData::NAME_DefaultItemType("Item");

UItemData::UItemData(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ItemType.Name = UItemData::NAME_DefaultItemType;
}

#if WITH_EDITOR
EDataValidationResult UItemData::IsDataValid(FDataValidationContext& Context) const
{
	auto Result{ CombineDataValidationResults(Super::IsDataValid(Context), EDataValidationResult::Valid) };

	// Validate ItemType

	if (!ItemType.IsValid())
	{
		Result = CombineDataValidationResults(Result, EDataValidationResult::Invalid);

		Context.AddError(FText::FromString(FString::Printf(TEXT("Invalid ItemType defined in %s"), *GetNameSafe(this))));
	}

	// Validate Infomations

	int32 Index{ 0 };
	for (const auto& Info : Infomations)
	{
		if (!Info)
		{
			Result = CombineDataValidationResults(Result, EDataValidationResult::Invalid);

			Context.AddError(FText::FromString(FString::Printf(TEXT("Invalid Info defined in Infomations[%d] in %s"), Index, *GetNameSafe(this))));
		}
		else
		{
			Result = CombineDataValidationResults(Result, Info->IsDataValid(Context));
		}

		Index++;
	}

#if WITH_EDITORONLY_DATA
	PrimaryAssetId = GetIdentifierString();
#endif

	return Result;
}
#endif


FPrimaryAssetId UItemData::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(FPrimaryAssetType(ItemType.Name), GetFName());
}

FString UItemData::GetIdentifierString() const
{
	return GetPrimaryAssetId().ToString();
}


const UItemInfo* UItemData::FindInfoByClass(TSubclassOf<UItemInfo> InClass) const
{
	for (const auto& Info : Infomations)
	{
		if (Info->IsA(InClass))
		{
			return Info;
		}
	}

	return nullptr;
}
