// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class UE43rdPersonCPPEditorTarget : TargetRules
{
	public UE43rdPersonCPPEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		ExtraModuleNames.Add("UE43rdPersonCPP");
	}
}
