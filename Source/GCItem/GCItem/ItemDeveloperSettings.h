// Copyright (C) 2024 owoDra

#pragma once

#include "Engine/DeveloperSettings.h"

#include "ItemDeveloperSettings.generated.h"


/**
 * Settings for a Game framework.
 */
UCLASS(Config = "Game", Defaultconfig, meta = (DisplayName = "Game Item Core"))
class GCITEM_API UItemDeveloperSettings : public UDeveloperSettings
{
public:
	GENERATED_BODY()
public:
	UItemDeveloperSettings();

	///////////////////////////////////////////////
	// Primary Asset Type
public:
	//
	// List of Observer classes to be created in GameFeaturePolicy
	//
	UPROPERTY(Config, EditAnywhere, Category = "Primary Asset Type", meta = (NoElementDuplicate))
	TArray<FString> ItemTypeDefinitions;

public:
	UFUNCTION()
	static const TArray<FString>& GetItemTypeDefinitions();
};

