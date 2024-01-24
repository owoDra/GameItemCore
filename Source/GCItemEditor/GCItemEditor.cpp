// Copyright (C) 2024 owoDra

#include "GCItemEditor.h"

#include "PropertyCustomization/PropertyCustom_Picker_ItemType.h"
#include "AssetTypeAction/AssetTypeAction_ItemData.h"

IMPLEMENT_MODULE(FGCItemEditorModule, GCItemEditor)


#define LOCTEXT_NAMESPACE "GCItemEditorModule"

void FGCItemEditorModule::StartupModule()
{
	RegisterPropertyCustomizations();
	RegisterAssetTypeActions();
}

void FGCItemEditorModule::ShutdownModule()
{
	UnregisterPropertyCustomizations();
	UnregisterAssetTypeActions();
}


void FGCItemEditorModule::RegisterPropertyCustomizations()
{
	if (!FModuleManager::Get().IsModuleLoaded(NAME_PropertyEditorModule))
	{
		return;
	}

	auto& PropertyModule{ FModuleManager::LoadModuleChecked<FPropertyEditorModule>(NAME_PropertyEditorModule) };

	FPropertyCustom_Picker_ItemType::RegisterToPropertyEditorModule(PropertyModule);

	PropertyModule.NotifyCustomizationModuleChanged();
}

void FGCItemEditorModule::UnregisterPropertyCustomizations()
{
	if (!FModuleManager::Get().IsModuleLoaded(NAME_PropertyEditorModule))
	{
		return;
	}

	auto& PropertyModule{ FModuleManager::LoadModuleChecked<FPropertyEditorModule>(NAME_PropertyEditorModule) };

	FPropertyCustom_Picker_ItemType::UnregisterToPropertyEditorModule(PropertyModule);
}


void FGCItemEditorModule::RegisterAssetTypeActionCategory()
{
	static const FName CategoryKey{ TEXT("GameXXX") };
	static const FText CategoryDisplayName{ LOCTEXT("GameXXXCategory", "Item") };

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
