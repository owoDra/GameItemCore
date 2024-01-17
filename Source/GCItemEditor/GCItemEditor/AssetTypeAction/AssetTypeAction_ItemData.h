// Copyright (C) 2024 owoDra

#pragma once

#include "Factories/Factory.h"
#include "AssetTypeActions_Base.h"

#include "AssetTypeAction_ItemData.generated.h"

class UItemData;


/**
 * Class for creating SettingData in the context menu of asset creation
 */
UCLASS()
class UItemDataFactory : public UFactory
{
public:
	GENERATED_BODY()
public:
	UItemDataFactory();

protected:
	UPROPERTY(EditAnywhere, Category = "DataAsset")
	TSubclassOf<UItemData> DataAssetClass;

public:
	virtual FText GetDisplayName() const override;
	virtual bool ShouldShowInNewMenu() const override { return true; }
	virtual bool DoesSupportClass(UClass* Class) override;

	virtual bool ConfigureProperties() override;
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;

};


/**
 * Class to add a SettingData creation item to the context menu of an asset creation
 */
class FAssetTypeAction_ItemData : public FAssetTypeActions_Base
{
public:
	virtual ~FAssetTypeAction_ItemData() override = default;

public:
	virtual FText GetName() const override;
	virtual FText GetAssetDescription(const FAssetData& AssetData) const override;
	virtual FColor GetTypeColor() const override;
	virtual uint32 GetCategories() override;
	virtual UClass* GetSupportedClass() const override;

};
