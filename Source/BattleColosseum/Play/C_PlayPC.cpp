// Fill out your copyright notice in the Description page of Project Settings.

#include "C_PlayPC.h"
#include "Kismet/GameplayStatics.h"
#include "C_SaveGame.h"
#include "UnrealNetwork.h"
#include "Play/C_PlayGM.h"


void AC_PlayPC::Load() {
	SaveGameRef = Cast<UC_SaveGame>(UGameplayStatics::LoadGameFromSlot(SaveGameRef->SaveGameName, 0));
	if (SaveGameRef) {
		MyInfo = SaveGameRef->MyInfo;
	}
}

void AC_PlayPC::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AC_PlayPC, MyInfo);
}

bool AC_PlayPC::PassCharacterToServer_Validate(FC_S_PlayerInfo NewInfo)
{
	return true;
}
void AC_PlayPC::PassCharacterToServer_Implementation(FC_S_PlayerInfo NewInfo) {
	MyInfo = NewInfo;

	AC_PlayGM* GM = Cast<AC_PlayGM>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GM) {
		GM->SpawnCharacter_WaitTime(this, MyInfo.SelectCharacter.GameCharacter);
	}
}