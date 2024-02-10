// Copyright ShutInGaming

using UnrealBuildTool;
using System.Collections.Generic;

public class AuraARPGEditorTarget : TargetRules
{
	public AuraARPGEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "AuraARPG" } );
	}
}
