// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ProjectOdimhTarget : TargetRules
{
	public ProjectOdimhTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "ProjectOdimh" } );
	}
}
