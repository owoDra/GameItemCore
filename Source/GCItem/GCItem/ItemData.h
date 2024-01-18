// Copyright (C) 2024 owoDra

#pragma once

#include "Engine/DataAsset.h"

#include "Type/Picker/Picker_ItemType.h"

#include "ItemData.generated.h"

class UItemInfo;


/**
 * Base class for all items
 */
UCLASS(BlueprintType, Const)
class GCITEM_API UItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UItemData(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	static const FName NAME_DefaultItemType;
	
	/////////////////////////////////////////////////////////////////////////////////////
	// Validate Data
public:
#if WITH_EDITOR 
	virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;
#endif


	/////////////////////////////////////////////////////////////////////////////////////
	// Primary Asset
protected:
#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleAnywhere, Transient, Category = "Debug")
	mutable FString PrimaryAssetId;
#endif

	//
	// PrimaryAssetType name of this item data class
	//
	UPROPERTY(EditDefaultsOnly, Category = "Infomation")
	FPicker_ItemType ItemType;

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const;

	/**
	 * Return PrimaryAssetId as FString
	 */
	UFUNCTION(BlueprintCallable)
	FString GetIdentifierString() const;


	/////////////////////////////////////////////////////////////////////////////////////
	// Item Infomation
protected:
	//
	// Name displayed in game
	//
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Instanced, Category = "Infomation")
	TArray<TObjectPtr<const UItemInfo>> Infomations;

public:
	/**
	 * Find info object by class
	 */
	UFUNCTION(BlueprintCallable, Category = "Info", meta = (DeterminesOutputType = "InClass"))
	const UItemInfo* FindInfoByClass(TSubclassOf<UItemInfo> InClass) const;

	template <typename T>
	const T* FindInfo() const
	{
		return Cast<T>(FindInfoByClass(T::StaticClass()));
	}

};
