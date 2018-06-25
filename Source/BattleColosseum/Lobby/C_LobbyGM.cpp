// Fill out your copyright notice in the Description page of Project Settings.

#include "C_LobbyGM.h"
#include "Engine/World.h"

AC_LobbyGM::AC_LobbyGM() {
	bUseSeamlessTravel = true;
}

void AC_LobbyGM::MoveWorld(FString LevelName) {
	GetWorld()->ServerTravel(LevelName);
}