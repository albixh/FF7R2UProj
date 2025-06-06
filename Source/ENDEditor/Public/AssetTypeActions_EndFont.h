#pragma once

#include "CoreMinimal.h"
#include "AssetTypeCategories.h"
#include "AssetTypeActions_Base.h"
#include "EndFont.h"

class FAssetTypeActions_EndFont : public FAssetTypeActions_Base
{
public:
	FAssetTypeActions_EndFont(EAssetTypeCategories::Type InAssetCategory)
            : AssetCategory(InAssetCategory)
        {}
	// IAssetTypeActions Implementation
	virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions", "FAssetTypeActions_EndFont", "End Font"); }
	virtual FColor GetTypeColor() const override { return FColor::Magenta; }
	virtual UClass* GetSupportedClass() const override { return UEndFont::StaticClass(); }
	virtual uint32 GetCategories() override { return AssetCategory; }
    
private:
    EAssetTypeCategories::Type AssetCategory;
};
