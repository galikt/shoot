// Copyright Epic Games, Inc. All Rights Reserved.

#include "shootGameModeBase.h"
#include "MyCharacter.h"
#include "MyPlayerController.h"
#include "public/STUGameHud.h"

AshootGameModeBase::AshootGameModeBase()
{
	DefaultPawnClass = AMyCharacter::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
	HUDClass = ASTUGameHUD::StaticClass();
}