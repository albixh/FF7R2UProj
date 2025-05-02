using UnrealBuildTool;

public class ENDEditor : ModuleRules {
    public ENDEditor(ReadOnlyTargetRules Target) : base(Target) {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bLegacyPublicIncludePaths = false;
        ShadowVariableWarningLevel = WarningLevel.Warning;
        
        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "DeveloperSettings",
            "ToolMenus",
            "EditorStyle",
            "InputCore",
            "EndGame",
            "EndDataObject",
            "MovieScene",
            "MovieSceneTools",
            "Engine",
            "UnrealEd",
            "Slate",
            "SlateCore",
            "AssetTools",
            "Json",
            "ApplicationCore",
            "SQEXSEAD"
        });
    }
}
