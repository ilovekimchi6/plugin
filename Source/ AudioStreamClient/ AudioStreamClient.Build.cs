// Source/AudioStreamClient/AudioStreamClient.Build.cs

using UnrealBuildTool;

public class AudioStreamClient : ModuleRules
{
	public AudioStreamClient(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"InputCore",
                "WebSockets"
				// ... add other public dependencies that you statically link with here ...
			}
			);
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
                "AudioCapture"
				// ... add private dependencies that you statically link with here ...
			}
			);
	}
}