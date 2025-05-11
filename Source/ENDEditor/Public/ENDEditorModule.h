#pragma once
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Toolkits/IToolkitHost.h"
#include "Modules/ModuleInterface.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "Containers/Ticker.h"

class FENDEditorModule : public IModuleInterface,
	public IHasMenuExtensibility, public IHasToolBarExtensibility
{

public:
	FENDEditorModule() {}
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/** Gets the extensibility managers for outside entities to extend static mesh editor's menus and toolbars */
	virtual TSharedPtr<FExtensibilityManager> GetMenuExtensibilityManager() override { return MenuExtensibilityManager; }

	virtual TSharedPtr<FExtensibilityManager> GetToolBarExtensibilityManager() override { return ToolBarExtensibilityManager; }

	/** DataObject Editor app identifier string */
	static const FName DataObjectEditorAppIdentifier;
private:
	class FAssetTypeActions_EndEmissiveColorSettings* AssetAction;
	class FAssetTypeActions_EffectAppendixMesh* AssetAction2;
	class FAssetTypeActions_EndCameraSequence* AssetAction3;
	class FAssetTypeActions_EndCinemaSequence* AssetAction4;
	class FAssetTypeActions_EndAnimSet* AssetAction5;
	class FAssetTypeActions_EndAssetPack* AssetAction6;
	class FAssetTypeActions_ShaderResourceBuffer* AssetAction7;
	class FAssetTypeActions_EndDataObject* AssetAction8;
	class FAssetTypeActions_EndFont* AssetAction9;
	class FAssetTypeActions_SQEXSEADSound* AssetAction10;
	class FAssetTypeActions_SQEXSEADMusic* AssetAction11;
	class FAssetTypeActions_EndMaterialPack* AssetAction12;
    
	// Ticker handle for animating EffectAppendixMesh assets
	FDelegateHandle TickDelegateHandle;

	TSharedPtr<FExtensibilityManager> MenuExtensibilityManager;
	TSharedPtr<FExtensibilityManager> ToolBarExtensibilityManager;
};