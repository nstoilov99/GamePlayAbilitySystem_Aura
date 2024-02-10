// Copyright ShutInGaming

using UnrealBuildTool;
using System.Collections.Generic;

public class AuraARPGTarget : TargetRules
{
	public AuraARPGTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "AuraARPG" } );
	}
}
