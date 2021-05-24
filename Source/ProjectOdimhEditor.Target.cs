// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ProjectOdimhEditorTarget : TargetRules
{
	public ProjectOdimhEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "ProjectOdimh" } );
	}
}
