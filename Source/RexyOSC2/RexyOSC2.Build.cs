using UnrealBuildTool;

public class RexyOSC2 : ModuleRules
{
    public RexyOSC2(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "OSC" });
    }
}
