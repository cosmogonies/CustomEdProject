// Copyright Epic Games, Inc. All Rights Reserved.


using UnrealBuildTool;
 
public class CustomEdProjectEditor: ModuleRules
{
	public CustomEdProjectEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] {"Core", "CoreUObject", "Engine", "CustomEdProject"});

		// We also add Slate dependencies for Details Customization:
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });	
	}
}


