// Copyright (C) 2024 owoDra

#pragma once

#include "Info/ItemInfo.h"

#include "ItemInfo_UserFacing.generated.h"


/**
 * Basic information for users
 */
UCLASS(meta = (DisplayName = "User Facing Info"))
class GCITEM_API UItemInfo_UserFacing : public UItemInfo
{
	GENERATED_BODY()
public:
	UItemInfo_UserFacing(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "User Facing")
	FText DisplayName;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "User Facing")
	FText Description;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "User Facing", meta = (DisplayThumbnail = "true", AssetBundles = "Client", AllowedClasses = "/Script/Engine.Texture,/Script/Engine.MaterialInterface,/Script/Engine.SlateTextureAtlasInterface", DisallowedClasses = "/Script/MediaAssets.MediaTexture"))
	TSoftObjectPtr<UObject> Image;

};
