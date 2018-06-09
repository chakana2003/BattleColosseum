// Fill out your copyright notice in the Description page of Project Settings.

#include "C_SaveGame.h"
#include "C_S_PlayerInfo.h"
#include "UnrealNetwork.h"


UC_SaveGame::UC_SaveGame() {
	SaveGameName = "SAVEGAME";
	MyInfo = FC_S_PlayerInfo();
}

void UC_SaveGame::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UC_SaveGame, MyInfo);
}
