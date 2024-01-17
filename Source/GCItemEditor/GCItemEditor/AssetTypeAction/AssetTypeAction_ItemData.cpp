// Copyright (C) 2024 owoDra

#include "AssetTypeAction_ItemData.h"

#include "ItemData.h"
#include "GCItemEditor.h"

#include "Modules/ModuleManager.h"
#include "ClassViewerModule.h"
#include "ClassViewerFilter.h"
#include "AssetRegistry/AssetData.h"
#include "Kismet2/SClassPickerDialog.h"
#include "Kismet2/KismetEditorUtilities.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AssetTypeAction_ItemData)


#pragma region AssetClassParentFilter

/**
 * A copy of what is defined in EditorFactories.cpp
 * EditorFactories.cpp cannot be included, so the same is defined here
 */
class FAssetClassParentFilter : public IClassViewerFilter
{
public:
	FAssetClassParentFilter()
		: DisallowedClassFlags(CLASS_None), bDisallowBlueprintBase(false)
	{}

	/** All children of these classes will be included unless filtered out by another setting. */
	TSet< const UClass* > AllowedChildrenOfClasses;

	/** Disallowed class flags. */
	EClassFlags DisallowedClassFlags;

	/** Disallow blueprint base classes. */
	bool bDisallowBlueprintBase;

	virtual bool IsClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const UClass* InClass, TSharedRef< FClassViewerFilterFuncs > InFilterFuncs) override
	{
		bool bAllowed= !InClass->HasAnyClassFlags(DisallowedClassFlags)
			&& InClass->CanCreateAssetOfClass()
			&& InFilterFuncs->IfInChildOfClassesSet(AllowedChildrenOfClasses, InClass) != EFilterReturn::Failed;

		if (bAllowed && bDisallowBlueprintBase)
		{
			if (FKismetEditorUtilities::CanCreateBlueprintOfClass(InClass))
			{
				return false;
			}
		}

		return bAllowed;
	}

	virtual bool IsUnloadedClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const TSharedRef< const IUnloadedBlueprintData > InUnloadedClassData, TSharedRef< FClassViewerFilterFuncs > InFilterFuncs) override
	{
		if (bDisallowBlueprintBase)
		{
			return false;
		}

		return !InUnloadedClassData->HasAnyClassFlags(DisallowedClassFlags)
			&& InFilterFuncs->IfInChildOfClassesSet(AllowedChildrenOfClasses, InUnloadedClassData) != EFilterReturn::Failed;
	}
};

#pragma endregion


#define LOCTEXT_NAMESPACE "AssetTypeActions"

#pragma region SettingDataFactroy

UItemDataFactory::UItemDataFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UItemData::StaticClass();
}


FText UItemDataFactory::GetDisplayName() const
{
	return LOCTEXT("ItemData", "Item Data");
}

bool UItemDataFactory::DoesSupportClass(UClass* Class)
{
	return Class && Class->IsChildOf(GetSupportedClass());
}


bool UItemDataFactory::ConfigureProperties()
{
	// nullptr the DataAssetClass so we can check for selection

	DataAssetClass = nullptr;

	// Load the classviewer module to display a class picker

	FClassViewerModule& ClassViewerModule = FModuleManager::LoadModuleChecked<FClassViewerModule>("ClassViewer");

	// Fill in options

	FClassViewerInitializationOptions Options;
	Options.Mode = EClassViewerMode::ClassPicker;
	Options.NameTypeToDisplay = EClassViewerNameTypeToDisplay::DisplayName;
	TSharedPtr<FAssetClassParentFilter> Filter = MakeShareable(new FAssetClassParentFilter);
	Options.ClassFilters.Add(Filter.ToSharedRef());

	Filter->DisallowedClassFlags = CLASS_Abstract | CLASS_Deprecated | CLASS_NewerVersionExists | CLASS_HideDropDown;
	Filter->AllowedChildrenOfClasses.Add(UDataAsset::StaticClass());

	const FText TitleText = LOCTEXT("CreateItemDataOptions", "Pick Class For ItemData Instance");
	UClass* ChosenClass = nullptr;
	const bool bPressedOk = SClassPickerDialog::PickClass(TitleText, Options, ChosenClass, UItemData::StaticClass());

	if (bPressedOk)
	{
		DataAssetClass = ChosenClass;
	}

	return bPressedOk;
}

UObject* UItemDataFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	if (DataAssetClass != nullptr)
	{
		return NewObject<UItemData>(InParent, DataAssetClass, Name, Flags | RF_Transactional);
	}
	else
	{
		// if we have no data asset class, use the passed-in class instead

		check(Class->IsChildOf(UItemData::StaticClass()));
		return NewObject<UItemData>(InParent, Class, Name, Flags);
	}
}

#pragma endregion


#pragma region AssetTypeAction

FText FAssetTypeAction_ItemData::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_ItemData", "Item Data");
}

FText FAssetTypeAction_ItemData::GetAssetDescription(const FAssetData& AssetData) const
{
	return LOCTEXT("AssetDescription_ItemData", "Data asset representing the concept of an item.");
}

FColor FAssetTypeAction_ItemData::GetTypeColor() const
{
	return FColor::Orange;
}

uint32 FAssetTypeAction_ItemData::GetCategories()
{
	return FGCItemEditorModule::Category;
}

UClass* FAssetTypeAction_ItemData::GetSupportedClass() const
{
	return UItemData::StaticClass();
}

#pragma endregion

#undef LOCTEXT_NAMESPACE
