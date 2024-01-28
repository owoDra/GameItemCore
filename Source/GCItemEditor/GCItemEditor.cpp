// Copyright (C) 2024 owoDra

#include "GCItemEditor.h"

#include "AssetTypeAction/AssetTypeAction_ItemData.h"

IMPLEMENT_MODULE(FGCItemEditorModule, GCItemEditor)


#define LOCTEXT_NAMESPACE "GCItemEditorModule"

void FGCItemEditorModule::StartupModule()
{
	RegisterAssetTypeActions();
}

void FGCItemEditorModule::ShutdownModule()
{
	UnregisterAssetTypeActions();
}


void FGCItemEditorModule::RegisterAssetTypeActionCategory()
{
	static const FName CategoryKey{ TEXT("GameItem") };
	static const FText CategoryDisplayName{ LOCTEXT("GameItemCategory", "Item") };

	Category = IAssetTools::Get().RegisterAdvancedAssetCategory(CategoryKey, CategoryDisplayName);
}

void FGCItemEditorModule::RegisterAssetTypeActions()
{
	RegisterAssetTypeActionCategory();

	RegisterAsset<FAssetTypeAction_ItemData>(RegisteredAssetTypeActions);
}

void FGCItemEditorModule::UnregisterAssetTypeActions()
{
	UnregisterAssets(RegisteredAssetTypeActions);
}

void FGCItemEditorModule::UnregisterAssets(TArray<TSharedPtr<FAssetTypeActions_Base>>& RegisteredAssets)
{
	const auto* AssetToolsPtr{ FModuleManager::GetModulePtr<FAssetToolsModule>(NAME_AssetToolsModule) };
	if (!AssetToolsPtr)
	{
		return;
	}

	auto& AssetTools{ AssetToolsPtr->Get() };
	for (auto& AssetTypeActionIt : RegisteredAssets)
	{
		if (AssetTypeActionIt.IsValid())
		{
			AssetTools.UnregisterAssetTypeActions(AssetTypeActionIt.ToSharedRef());
		}
	}
}

#undef LOCTEXT_NAMESPACE
