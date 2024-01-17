// Copyright (C) 2024 owoDra

#include "PropertyCustom_Picker_ItemType.h"

#include "Type/Picker/Picker_ItemType.h"
#include "ItemDeveloperSettings.h"
#include "ItemData.h"

#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "IDetailChildrenBuilder.h"
#include "SSearchableComboBox.h"

const FName FPropertyCustom_Picker_ItemType::NAME_Picker_ItemTypeProperty(FPicker_ItemType::StaticStruct()->GetFName());


TSharedRef<IPropertyTypeCustomization> FPropertyCustom_Picker_ItemType::MakeInstance()
{
	return MakeShareable(new FPropertyCustom_Picker_ItemType());
}

void FPropertyCustom_Picker_ItemType::RegisterToPropertyEditorModule(FPropertyEditorModule& PropertyModule)
{
	PropertyModule.RegisterCustomPropertyTypeLayout(
		FPropertyCustom_Picker_ItemType::NAME_Picker_ItemTypeProperty,
		FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FPropertyCustom_Picker_ItemType::MakeInstance));
}

void FPropertyCustom_Picker_ItemType::UnregisterToPropertyEditorModule(FPropertyEditorModule& PropertyModule)
{
	PropertyModule.UnregisterCustomPropertyTypeLayout(FPropertyCustom_Picker_ItemType::NAME_Picker_ItemTypeProperty);
}


void FPropertyCustom_Picker_ItemType::CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	// Set callbacks for variable changes

	ParentPropertyHandle = PropertyHandle;

	// Added item about variable "Name"

	NamePropertyHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FPicker_ItemType, Name));
	if (NamePropertyHandle.IsValid())
	{
		// Initialize CombBox data

		InitSuggestList();

		RefreshSuggestList();

		// Build a widget for the currently selected ItemType

		FText TextRowText;
		NamePropertyHandle->GetValueAsDisplayText(TextRowText);

		const auto TextRowWidgetRef
		{
			SNew(STextBlock)
				.Text(TextRowText)
		};

		RowTextWidget = TextRowWidgetRef;

		// Build a widget about the suggest list

		const auto SearchableComboBoxRef
		{
			SNew(SSearchableComboBox)
				.OptionsSource(&SuggestListOptions)
				.OnGenerateWidget_Lambda(
					[](const TSharedPtr<FString> InItem) -> TSharedRef<SWidget>
					{
						return SNew(STextBlock).Text(FText::FromString(*InItem));
					}
				)
				.OnSelectionChanged(this, &ThisClass::HandleSuggestSelected)
				.ContentPadding(2.f)
				.MaxListHeight(200.f)
				.IsEnabled(true)
				.Content()
				[
					TextRowWidgetRef
				]
		};

		SuggestListWidget = SearchableComboBoxRef;

		// Build widgets for editable items

		HeaderRow
			.NameContent()
			[
				SNew(STextBlock)
					.Text(ParentPropertyHandle->GetPropertyDisplayName())
					.Font(IDetailLayoutBuilder::GetDetailFont())
			]
			.ValueContent()
			[
				SNew(SVerticalBox) + SVerticalBox::Slot()
										.AutoHeight()
										.VAlign(VAlign_Fill)
										.Padding(0.f)
										[
											SearchableComboBoxRef
										]
			];
	}
}

void FPropertyCustom_Picker_ItemType::CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
}


void FPropertyCustom_Picker_ItemType::SetItemTypeNameValue(FName Value)
{
	if (NamePropertyHandle.IsValid())
	{
		NamePropertyHandle->SetValue(Value);
	}

	if (const auto & TextWidget{ RowTextWidget.Pin() })
	{
		TextWidget->SetText(FText::FromName(Value));
	}
}

void FPropertyCustom_Picker_ItemType::InitSuggestList()
{
	if (!DefaultOption.IsValid())
	{
		TSharedPtr<FString> NoneStringPtr{ MakeShareable(new FString(UItemData::NAME_DefaultItemType.ToString())) };
		DefaultOption = NoneStringPtr;
		SuggestListOptions.EmplaceAt(0, MoveTemp(NoneStringPtr));
	}
}

void FPropertyCustom_Picker_ItemType::ResetSuggestList()
{
	for (int32 Idx{ SuggestListOptions.Num() - 1 }; Idx >= 0; --Idx)
	{
		if (!SuggestListOptions.IsValidIndex(Idx))
		{
			continue;
		}

		auto StringPtrIt{ SuggestListOptions[Idx] };
		if (StringPtrIt != DefaultOption)
		{
			StringPtrIt.Reset();
			SuggestListOptions.RemoveAt(Idx);
		}
	}
}

void FPropertyCustom_Picker_ItemType::RefreshSuggestList()
{
	ResetSuggestList();

	if (!NamePropertyHandle.IsValid())
	{
		return;
	}

	// Load developer settings

	const auto* DevSettings{ GetDefault<UItemDeveloperSettings>() };
	if (!ensureMsgf(DevSettings, TEXT("Can't accese GameItemCore's DeveloperSettings")))
	{
		return;
	}

	// Create a list from DeveloperSettings

	FName SelectedSettingSourceName{ UItemData::NAME_DefaultItemType };
	NamePropertyHandle->GetValue(SelectedSettingSourceName);

	auto bFoundSpecifiedName{ false };
	for (const auto& Each : DevSettings->ItemTypeDefinitions)
	{
		if (SelectedSettingSourceName == Each)
		{
			bFoundSpecifiedName = true;
		}

		SuggestListOptions.Emplace(MakeShareable(new FString(Each.ToString())));
	}

	// Set to Default if not selected.

	if (!bFoundSpecifiedName)
	{
		SetItemTypeNameValue(UItemData::NAME_DefaultItemType);
	}
}

void FPropertyCustom_Picker_ItemType::HandleSuggestSelected(TSharedPtr<FString> SelectedStringPtr, ESelectInfo::Type SelectInfo)
{
	if (const auto* SelectedString{ SelectedStringPtr.Get() })
	{
		SetItemTypeNameValue(**SelectedString);
	}
}
