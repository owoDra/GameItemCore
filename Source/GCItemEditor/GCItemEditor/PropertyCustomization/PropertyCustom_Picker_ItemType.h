// Copyright (C) 2024 owoDra

#pragma once

#include "IPropertyTypeCustomization.h"

class UObject;
class STextBlock;
class SSearchableComboBox;


/**
 * Class to customize editing in the editor of the type structure that selects the name of the ItemType registered in Developer Settings.
 */
class FPropertyCustom_Picker_ItemType : public IPropertyTypeCustomization
{
private:
	typedef FPropertyCustom_Picker_ItemType ThisClass;

	static const FName NAME_Picker_ItemTypeProperty;

protected:
	//
	// Slate widget to display current values
	//
	TWeakPtr<STextBlock> RowTextWidget{ nullptr };

	//
	// Slate widget for displaying selectable values
	//
	TWeakPtr<SSearchableComboBox> SuggestListWidget{ nullptr };

	//
	// Option list in CombBox
	//
	TArray<TSharedPtr<FString>> SuggestListOptions;

	//
	// Option name if no value is selected
	//
	TWeakPtr<FString> DefaultOption{ nullptr };

	//
	// Handle to the Picker variable to be edited
	//
	TSharedPtr<IPropertyHandle> ParentPropertyHandle{ nullptr };

	//
	// Handle to the Name variable of the Picker structure
	//
	TSharedPtr<IPropertyHandle> NamePropertyHandle{ nullptr };

public:
	/**
	 * Create an instance of this class
	 */
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	/**
	 * Register this class in the module
	 */
	static void RegisterToPropertyEditorModule(FPropertyEditorModule& PropertyModule);

	/**
	 * Unregister this class from the module
	 */
	static void UnregisterToPropertyEditorModule(FPropertyEditorModule& PropertyModule);


public:
	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;


protected:
	/**
	 * Set the ItemType of the selected item.
	 */
	void SetItemTypeNameValue(FName Value);

	/**
	 * Add an empty entry to the CombBox once and deselect User
	 */
	void InitSuggestList();

	/**
	 * Delete everything in CombBox to DefaultOption only
	 */
	void ResetSuggestList();

	/**
	 * Update list based on DeveloperSettings
	 * 
	 * Tips:
	 *	Called when there is a change in a variable
	 */
	void RefreshSuggestList();

	/**
	 * Disable list
	 */
	void InvalidateSuggestList();

	/**
	 * Called when ItemType is selected from CombBox
	 */
	void HandleSuggestSelected(TSharedPtr<FString> SelectedStringPtr, ESelectInfo::Type SelectInfo);

};
