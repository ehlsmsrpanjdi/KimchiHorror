// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HorrorProtoKimchi : ModuleRules
{
	public HorrorProtoKimchi(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"HorrorProtoKimchi",
			"HorrorProtoKimchi/Variant_Platforming",
			"HorrorProtoKimchi/Variant_Platforming/Animation",
			"HorrorProtoKimchi/Variant_Combat",
			"HorrorProtoKimchi/Variant_Combat/AI",
			"HorrorProtoKimchi/Variant_Combat/Animation",
			"HorrorProtoKimchi/Variant_Combat/Gameplay",
			"HorrorProtoKimchi/Variant_Combat/Interfaces",
			"HorrorProtoKimchi/Variant_Combat/UI",
			"HorrorProtoKimchi/Variant_SideScrolling",
			"HorrorProtoKimchi/Variant_SideScrolling/AI",
			"HorrorProtoKimchi/Variant_SideScrolling/Gameplay",
			"HorrorProtoKimchi/Variant_SideScrolling/Interfaces",
			"HorrorProtoKimchi/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
