// Copyright (C) 2024 owoDra

#include "ItemDeveloperSettings.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ItemDeveloperSettings)


UItemDeveloperSettings::UItemDeveloperSettings()
{
	CategoryName = TEXT("Game XXX Core");
	SectionName = TEXT("Game Item Core");
}

#if WITH_EDITORONLY_DATA

const TArray<FString>& UItemDeveloperSettings::GetItemTypeDefinitions()
{
	return GetDefault<UItemDeveloperSettings>()->ItemTypeDefinitions;
}

#endif
