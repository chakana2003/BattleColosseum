// Fill out your copyright notice in the Description page of Project Settings.

#include "C_LobbyGM.h"
#include "Engine/World.h"

void AC_LobbyGM::MoveWorld(FString LevelName) {
	GetWorld()->ServerTravel(LevelName);
}